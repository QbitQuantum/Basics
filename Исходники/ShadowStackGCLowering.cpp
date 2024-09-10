/// runOnFunction - Insert code to maintain the shadow stack.
bool ShadowStackGCLowering::runOnFunction(Function &F) {
  // Quick exit for functions that do not use the shadow stack GC.
  if (!F.hasGC() ||
      F.getGC() != std::string("shadow-stack"))
    return false;
  
  LLVMContext &Context = F.getContext();

  // Find calls to llvm.gcroot.
  CollectRoots(F);

  // If there are no roots in this function, then there is no need to add a
  // stack map entry for it.
  if (Roots.empty())
    return false;

  // Build the constant map and figure the type of the shadow stack entry.
  Value *FrameMap = GetFrameMap(F);
  Type *ConcreteStackEntryTy = GetConcreteStackEntryType(F);

  // Build the shadow stack entry at the very start of the function.
  BasicBlock::iterator IP = F.getEntryBlock().begin();
  IRBuilder<> AtEntry(IP->getParent(), IP);

  Instruction *StackEntry =
      AtEntry.CreateAlloca(ConcreteStackEntryTy, nullptr, "gc_frame");

  while (isa<AllocaInst>(IP))
    ++IP;
  AtEntry.SetInsertPoint(IP->getParent(), IP);

  // Initialize the map pointer and load the current head of the shadow stack.
  Instruction *CurrentHead = AtEntry.CreateLoad(Head, "gc_currhead");
  Instruction *EntryMapPtr = CreateGEP(Context, AtEntry, ConcreteStackEntryTy,
                                       StackEntry, 0, 1, "gc_frame.map");
  AtEntry.CreateStore(FrameMap, EntryMapPtr);

  // After all the allocas...
  for (unsigned I = 0, E = Roots.size(); I != E; ++I) {
    // For each root, find the corresponding slot in the aggregate...
    Value *SlotPtr = CreateGEP(Context, AtEntry, ConcreteStackEntryTy,
                               StackEntry, 1 + I, "gc_root");

    // And use it in lieu of the alloca.
    AllocaInst *OriginalAlloca = Roots[I].second;
    SlotPtr->takeName(OriginalAlloca);
    OriginalAlloca->replaceAllUsesWith(SlotPtr);
  }

  // Move past the original stores inserted by GCStrategy::InitRoots. This isn't
  // really necessary (the collector would never see the intermediate state at
  // runtime), but it's nicer not to push the half-initialized entry onto the
  // shadow stack.
  while (isa<StoreInst>(IP))
    ++IP;
  AtEntry.SetInsertPoint(IP->getParent(), IP);

  // Push the entry onto the shadow stack.
  Instruction *EntryNextPtr = CreateGEP(Context, AtEntry, ConcreteStackEntryTy,
                                        StackEntry, 0, 0, "gc_frame.next");
  Instruction *NewHeadVal = CreateGEP(Context, AtEntry, ConcreteStackEntryTy,
                                      StackEntry, 0, "gc_newhead");
  AtEntry.CreateStore(CurrentHead, EntryNextPtr);
  AtEntry.CreateStore(NewHeadVal, Head);

  // For each instruction that escapes...
  EscapeEnumerator EE(F, "gc_cleanup");
  while (IRBuilder<> *AtExit = EE.Next()) {
    // Pop the entry from the shadow stack. Don't reuse CurrentHead from
    // AtEntry, since that would make the value live for the entire function.
    Instruction *EntryNextPtr2 =
        CreateGEP(Context, *AtExit, ConcreteStackEntryTy, StackEntry, 0, 0,
                  "gc_frame.next");
    Value *SavedHead = AtExit->CreateLoad(EntryNextPtr2, "gc_savedhead");
    AtExit->CreateStore(SavedHead, Head);
  }

  // Delete the original allocas (which are no longer used) and the intrinsic
  // calls (which are no longer valid). Doing this last avoids invalidating
  // iterators.
  for (unsigned I = 0, E = Roots.size(); I != E; ++I) {
    Roots[I].first->eraseFromParent();
    Roots[I].second->eraseFromParent();
  }

  Roots.clear();
  return true;
}