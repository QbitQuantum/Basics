/// handleEndBlock - Remove dead stores to stack-allocated locations in the
/// function end block.  Ex:
/// %A = alloca i32
/// ...
/// store i32 1, i32* %A
/// ret void
bool DSE::handleEndBlock(BasicBlock &BB) {
  bool MadeChange = false;

  // Keep track of all of the stack objects that are dead at the end of the
  // function.
  SmallSetVector<Value*, 16> DeadStackObjects;

  // Find all of the alloca'd pointers in the entry block.
  BasicBlock *Entry = BB.getParent()->begin();
  for (BasicBlock::iterator I = Entry->begin(), E = Entry->end(); I != E; ++I) {
    if (isa<AllocaInst>(I))
      DeadStackObjects.insert(I);

    // Okay, so these are dead heap objects, but if the pointer never escapes
    // then it's leaked by this function anyways.
    else if (isAllocLikeFn(I, TLI) && !PointerMayBeCaptured(I, true, true))
      DeadStackObjects.insert(I);
  }

  // Treat byval or inalloca arguments the same, stores to them are dead at the
  // end of the function.
  for (Function::arg_iterator AI = BB.getParent()->arg_begin(),
       AE = BB.getParent()->arg_end(); AI != AE; ++AI)
    if (AI->hasByValOrInAllocaAttr())
      DeadStackObjects.insert(AI);

  // Scan the basic block backwards
  for (BasicBlock::iterator BBI = BB.end(); BBI != BB.begin(); ){
    --BBI;

    // If we find a store, check to see if it points into a dead stack value.
    if (hasMemoryWrite(BBI, TLI) && isRemovable(BBI)) {
      // See through pointer-to-pointer bitcasts
      SmallVector<Value *, 4> Pointers;
      GetUnderlyingObjects(getStoredPointerOperand(BBI), Pointers);

      // Stores to stack values are valid candidates for removal.
      bool AllDead = true;
      for (SmallVectorImpl<Value *>::iterator I = Pointers.begin(),
           E = Pointers.end(); I != E; ++I)
        if (!DeadStackObjects.count(*I)) {
          AllDead = false;
          break;
        }

      if (AllDead) {
        Instruction *Dead = BBI++;

        DEBUG(dbgs() << "DSE: Dead Store at End of Block:\n  DEAD: "
                     << *Dead << "\n  Objects: ";
              for (SmallVectorImpl<Value *>::iterator I = Pointers.begin(),
                   E = Pointers.end(); I != E; ++I) {
                dbgs() << **I;
                if (std::next(I) != E)
                  dbgs() << ", ";
              }
              dbgs() << '\n');

        // DCE instructions only used to calculate that store.
        DeleteDeadInstruction(Dead, *MD, TLI, &DeadStackObjects);
        ++NumFastStores;
        MadeChange = true;
        continue;
      }
    }

    // Remove any dead non-memory-mutating instructions.
    if (isInstructionTriviallyDead(BBI, TLI)) {
      Instruction *Inst = BBI++;
      DeleteDeadInstruction(Inst, *MD, TLI, &DeadStackObjects);
      ++NumFastOther;
      MadeChange = true;
      continue;
    }

    if (isa<AllocaInst>(BBI)) {
      // Remove allocas from the list of dead stack objects; there can't be
      // any references before the definition.
      DeadStackObjects.remove(BBI);
      continue;
    }

    if (CallSite CS = cast<Value>(BBI)) {
      // Remove allocation function calls from the list of dead stack objects;
      // there can't be any references before the definition.
      if (isAllocLikeFn(BBI, TLI))
        DeadStackObjects.remove(BBI);

      // If this call does not access memory, it can't be loading any of our
      // pointers.
      if (AA->doesNotAccessMemory(CS))
        continue;

      // If the call might load from any of our allocas, then any store above
      // the call is live.
      DeadStackObjects.remove_if([&](Value *I) {
        // See if the call site touches the value.
        AliasAnalysis::ModRefResult A =
            AA->getModRefInfo(CS, I, getPointerSize(I, *AA));

        return A == AliasAnalysis::ModRef || A == AliasAnalysis::Ref;
      });

      // If all of the allocas were clobbered by the call then we're not going
      // to find anything else to process.
      if (DeadStackObjects.empty())
        break;

      continue;
    }

    AliasAnalysis::Location LoadedLoc;

    // If we encounter a use of the pointer, it is no longer considered dead
    if (LoadInst *L = dyn_cast<LoadInst>(BBI)) {
      if (!L->isUnordered()) // Be conservative with atomic/volatile load
        break;
      LoadedLoc = AA->getLocation(L);
    } else if (VAArgInst *V = dyn_cast<VAArgInst>(BBI)) {
      LoadedLoc = AA->getLocation(V);
    } else if (MemTransferInst *MTI = dyn_cast<MemTransferInst>(BBI)) {
      LoadedLoc = AA->getLocationForSource(MTI);
    } else if (!BBI->mayReadFromMemory()) {
      // Instruction doesn't read memory.  Note that stores that weren't removed
      // above will hit this case.
      continue;
    } else {
      // Unknown inst; assume it clobbers everything.
      break;
    }

    // Remove any allocas from the DeadPointer set that are loaded, as this
    // makes any stores above the access live.
    RemoveAccessedObjects(LoadedLoc, DeadStackObjects);

    // If all of the allocas were clobbered by the access then we're not going
    // to find anything else to process.
    if (DeadStackObjects.empty())
      break;
  }