/// PromoteAliasSet - Try to promote memory values to scalars by sinking
/// stores out of the loop and moving loads to before the loop.  We do this by
/// looping over the stores in the loop, looking for stores to Must pointers
/// which are loop invariant.
///
void LICM::PromoteAliasSet(AliasSet &AS) {
  // We can promote this alias set if it has a store, if it is a "Must" alias
  // set, if the pointer is loop invariant, and if we are not eliminating any
  // volatile loads or stores.
  if (AS.isForwardingAliasSet() || !AS.isMod() || !AS.isMustAlias() ||
      AS.isVolatile() || !CurLoop->isLoopInvariant(AS.begin()->getValue()))
    return;
  
  assert(!AS.empty() &&
         "Must alias set should have at least one pointer element in it!");
  Value *SomePtr = AS.begin()->getValue();

  // It isn't safe to promote a load/store from the loop if the load/store is
  // conditional.  For example, turning:
  //
  //    for () { if (c) *P += 1; }
  //
  // into:
  //
  //    tmp = *P;  for () { if (c) tmp +=1; } *P = tmp;
  //
  // is not safe, because *P may only be valid to access if 'c' is true.
  // 
  // It is safe to promote P if all uses are direct load/stores and if at
  // least one is guaranteed to be executed.
  bool GuaranteedToExecute = false;
  
  SmallVector<Instruction*, 64> LoopUses;
  SmallPtrSet<Value*, 4> PointerMustAliases;

  // Check that all of the pointers in the alias set have the same type.  We
  // cannot (yet) promote a memory location that is loaded and stored in
  // different sizes.
  for (AliasSet::iterator ASI = AS.begin(), E = AS.end(); ASI != E; ++ASI) {
    Value *ASIV = ASI->getValue();
    PointerMustAliases.insert(ASIV);
    
    // Check that all of the pointers in the alias set have the same type.  We
    // cannot (yet) promote a memory location that is loaded and stored in
    // different sizes.
    if (SomePtr->getType() != ASIV->getType())
      return;
    
    for (Value::use_iterator UI = ASIV->use_begin(), UE = ASIV->use_end();
         UI != UE; ++UI) {
      // Ignore instructions that are outside the loop.
      Instruction *Use = dyn_cast<Instruction>(*UI);
      if (!Use || !CurLoop->contains(Use))
        continue;
      
      // If there is an non-load/store instruction in the loop, we can't promote
      // it.
      if (isa<LoadInst>(Use))
        assert(!cast<LoadInst>(Use)->isVolatile() && "AST broken");
      else if (isa<StoreInst>(Use)) {
        assert(!cast<StoreInst>(Use)->isVolatile() && "AST broken");
        if (Use->getOperand(0) == ASIV) return;
      } else
        return; // Not a load or store.
      
      if (!GuaranteedToExecute)
        GuaranteedToExecute = isSafeToExecuteUnconditionally(*Use);
      
      LoopUses.push_back(Use);
    }
  }
  
  // If there isn't a guaranteed-to-execute instruction, we can't promote.
  if (!GuaranteedToExecute)
    return;
  
  // Otherwise, this is safe to promote, lets do it!
  DEBUG(dbgs() << "LICM: Promoting value stored to in loop: " <<*SomePtr<<'\n');  
  Changed = true;
  ++NumPromoted;

  // We use the SSAUpdater interface to insert phi nodes as required.
  SmallVector<PHINode*, 16> NewPHIs;
  SSAUpdater SSA(&NewPHIs);
  
  // It wants to know some value of the same type as what we'll be inserting.
  Value *SomeValue;
  if (isa<LoadInst>(LoopUses[0]))
    SomeValue = LoopUses[0];
  else
    SomeValue = cast<StoreInst>(LoopUses[0])->getOperand(0);
  SSA.Initialize(SomeValue->getType(), SomeValue->getName());

  // First step: bucket up uses of the pointers by the block they occur in.
  // This is important because we have to handle multiple defs/uses in a block
  // ourselves: SSAUpdater is purely for cross-block references.
  // FIXME: Want a TinyVector<Instruction*> since there is usually 0/1 element.
  DenseMap<BasicBlock*, std::vector<Instruction*> > UsesByBlock;
  for (unsigned i = 0, e = LoopUses.size(); i != e; ++i) {
    Instruction *User = LoopUses[i];
    UsesByBlock[User->getParent()].push_back(User);
  }
  
  // Okay, now we can iterate over all the blocks in the loop with uses,
  // processing them.  Keep track of which loads are loading a live-in value.
  SmallVector<LoadInst*, 32> LiveInLoads;
  DenseMap<Value*, Value*> ReplacedLoads;
  
  for (unsigned LoopUse = 0, e = LoopUses.size(); LoopUse != e; ++LoopUse) {
    Instruction *User = LoopUses[LoopUse];
    std::vector<Instruction*> &BlockUses = UsesByBlock[User->getParent()];
    
    // If this block has already been processed, ignore this repeat use.
    if (BlockUses.empty()) continue;
    
    // Okay, this is the first use in the block.  If this block just has a
    // single user in it, we can rewrite it trivially.
    if (BlockUses.size() == 1) {
      // If it is a store, it is a trivial def of the value in the block.
      if (isa<StoreInst>(User)) {
        SSA.AddAvailableValue(User->getParent(),
                              cast<StoreInst>(User)->getOperand(0));
      } else {
        // Otherwise it is a load, queue it to rewrite as a live-in load.
        LiveInLoads.push_back(cast<LoadInst>(User));
      }
      BlockUses.clear();
      continue;
    }
    
    // Otherwise, check to see if this block is all loads.  If so, we can queue
    // them all as live in loads.
    bool HasStore = false;
    for (unsigned i = 0, e = BlockUses.size(); i != e; ++i) {
      if (isa<StoreInst>(BlockUses[i])) {
        HasStore = true;
        break;
      }
    }
    
    if (!HasStore) {
      for (unsigned i = 0, e = BlockUses.size(); i != e; ++i)
        LiveInLoads.push_back(cast<LoadInst>(BlockUses[i]));
      BlockUses.clear();
      continue;
    }

    // Otherwise, we have mixed loads and stores (or just a bunch of stores).
    // Since SSAUpdater is purely for cross-block values, we need to determine
    // the order of these instructions in the block.  If the first use in the
    // block is a load, then it uses the live in value.  The last store defines
    // the live out value.  We handle this by doing a linear scan of the block.
    BasicBlock *BB = User->getParent();
    Value *StoredValue = 0;
    for (BasicBlock::iterator II = BB->begin(), E = BB->end(); II != E; ++II) {
      if (LoadInst *L = dyn_cast<LoadInst>(II)) {
        // If this is a load from an unrelated pointer, ignore it.
        if (!PointerMustAliases.count(L->getOperand(0))) continue;

        // If we haven't seen a store yet, this is a live in use, otherwise
        // use the stored value.
        if (StoredValue) {
          L->replaceAllUsesWith(StoredValue);
          ReplacedLoads[L] = StoredValue;
        } else {
          LiveInLoads.push_back(L);
        }
        continue;
      }
      
      if (StoreInst *S = dyn_cast<StoreInst>(II)) {
        // If this is a store to an unrelated pointer, ignore it.
        if (!PointerMustAliases.count(S->getOperand(1))) continue;

        // Remember that this is the active value in the block.
        StoredValue = S->getOperand(0);
      }
    }
    
    // The last stored value that happened is the live-out for the block.
    assert(StoredValue && "Already checked that there is a store in block");
    SSA.AddAvailableValue(BB, StoredValue);
    BlockUses.clear();
  }
  
  // Now that all the intra-loop values are classified, set up the preheader.
  // It gets a load of the pointer we're promoting, and it is the live-out value
  // from the preheader.
  LoadInst *PreheaderLoad = new LoadInst(SomePtr,SomePtr->getName()+".promoted",
                                         Preheader->getTerminator());
  SSA.AddAvailableValue(Preheader, PreheaderLoad);

  // Now that the preheader is good to go, set up the exit blocks.  Each exit
  // block gets a store of the live-out values that feed them.  Since we've
  // already told the SSA updater about the defs in the loop and the preheader
  // definition, it is all set and we can start using it.
  SmallVector<BasicBlock*, 8> ExitBlocks;
  CurLoop->getUniqueExitBlocks(ExitBlocks);
  for (unsigned i = 0, e = ExitBlocks.size(); i != e; ++i) {
    BasicBlock *ExitBlock = ExitBlocks[i];
    Value *LiveInValue = SSA.GetValueInMiddleOfBlock(ExitBlock);
    Instruction *InsertPos = ExitBlock->getFirstNonPHI();
    new StoreInst(LiveInValue, SomePtr, InsertPos);
  }

  // Okay, now we rewrite all loads that use live-in values in the loop,
  // inserting PHI nodes as necessary.
  for (unsigned i = 0, e = LiveInLoads.size(); i != e; ++i) {
    LoadInst *ALoad = LiveInLoads[i];
    Value *NewVal = SSA.GetValueInMiddleOfBlock(ALoad->getParent());
    ALoad->replaceAllUsesWith(NewVal);
    CurAST->copyValue(ALoad, NewVal);
    ReplacedLoads[ALoad] = NewVal;
  }
  
  // If the preheader load is itself a pointer, we need to tell alias analysis
  // about the new pointer we created in the preheader block and about any PHI
  // nodes that just got inserted.
  if (PreheaderLoad->getType()->isPointerTy()) {
    // Copy any value stored to or loaded from a must-alias of the pointer.
    CurAST->copyValue(SomeValue, PreheaderLoad);
    
    for (unsigned i = 0, e = NewPHIs.size(); i != e; ++i)
      CurAST->copyValue(SomeValue, NewPHIs[i]);
  }
  
  // Now that everything is rewritten, delete the old instructions from the body
  // of the loop.  They should all be dead now.
  for (unsigned i = 0, e = LoopUses.size(); i != e; ++i) {
    Instruction *User = LoopUses[i];
    
    // If this is a load that still has uses, then the load must have been added
    // as a live value in the SSAUpdate data structure for a block (e.g. because
    // the loaded value was stored later).  In this case, we need to recursively
    // propagate the updates until we get to the real value.
    if (!User->use_empty()) {
      Value *NewVal = ReplacedLoads[User];
      assert(NewVal && "not a replaced load?");
      
      // Propagate down to the ultimate replacee.  The intermediately loads
      // could theoretically already have been deleted, so we don't want to
      // dereference the Value*'s.
      DenseMap<Value*, Value*>::iterator RLI = ReplacedLoads.find(NewVal);
      while (RLI != ReplacedLoads.end()) {
        NewVal = RLI->second;
        RLI = ReplacedLoads.find(NewVal);
      }
      
      User->replaceAllUsesWith(NewVal);
      CurAST->copyValue(User, NewVal);
    }
    
    CurAST->deleteValue(User);
    User->eraseFromParent();
  }
  
  // fwew, we're done!
}