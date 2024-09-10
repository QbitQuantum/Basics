/// \brief Peel off the first \p PeelCount iterations of loop \p L.
///
/// Note that this does not peel them off as a single straight-line block.
/// Rather, each iteration is peeled off separately, and needs to check the
/// exit condition.
/// For loops that dynamically execute \p PeelCount iterations or less
/// this provides a benefit, since the peeled off iterations, which account
/// for the bulk of dynamic execution, can be further simplified by scalar
/// optimizations.
bool llvm::peelLoop(Loop *L, unsigned PeelCount, LoopInfo *LI,
                    ScalarEvolution *SE, DominatorTree *DT,
                    bool PreserveLCSSA) {
  if (!canPeel(L))
    return false;

  LoopBlocksDFS LoopBlocks(L);
  LoopBlocks.perform(LI);

  BasicBlock *Header = L->getHeader();
  BasicBlock *PreHeader = L->getLoopPreheader();
  BasicBlock *Latch = L->getLoopLatch();
  BasicBlock *Exit = L->getUniqueExitBlock();

  Function *F = Header->getParent();

  // Set up all the necessary basic blocks. It is convenient to split the
  // preheader into 3 parts - two blocks to anchor the peeled copy of the loop
  // body, and a new preheader for the "real" loop.

  // Peeling the first iteration transforms.
  //
  // PreHeader:
  // ...
  // Header:
  //   LoopBody
  //   If (cond) goto Header
  // Exit:
  //
  // into
  //
  // InsertTop:
  //   LoopBody
  //   If (!cond) goto Exit
  // InsertBot:
  // NewPreHeader:
  // ...
  // Header:
  //  LoopBody
  //  If (cond) goto Header
  // Exit:
  //
  // Each following iteration will split the current bottom anchor in two,
  // and put the new copy of the loop body between these two blocks. That is,
  // after peeling another iteration from the example above, we'll split 
  // InsertBot, and get:
  //
  // InsertTop:
  //   LoopBody
  //   If (!cond) goto Exit
  // InsertBot:
  //   LoopBody
  //   If (!cond) goto Exit
  // InsertBot.next:
  // NewPreHeader:
  // ...
  // Header:
  //  LoopBody
  //  If (cond) goto Header
  // Exit:

  BasicBlock *InsertTop = SplitEdge(PreHeader, Header, DT, LI);
  BasicBlock *InsertBot =
      SplitBlock(InsertTop, InsertTop->getTerminator(), DT, LI);
  BasicBlock *NewPreHeader =
      SplitBlock(InsertBot, InsertBot->getTerminator(), DT, LI);

  InsertTop->setName(Header->getName() + ".peel.begin");
  InsertBot->setName(Header->getName() + ".peel.next");
  NewPreHeader->setName(PreHeader->getName() + ".peel.newph");

  ValueToValueMapTy LVMap;

  // If we have branch weight information, we'll want to update it for the
  // newly created branches.
  BranchInst *LatchBR =
      cast<BranchInst>(cast<BasicBlock>(Latch)->getTerminator());
  unsigned HeaderIdx = (LatchBR->getSuccessor(0) == Header ? 0 : 1);

  uint64_t TrueWeight, FalseWeight;
  uint64_t ExitWeight = 0, BackEdgeWeight = 0;
  if (LatchBR->extractProfMetadata(TrueWeight, FalseWeight)) {
    ExitWeight = HeaderIdx ? TrueWeight : FalseWeight;
    BackEdgeWeight = HeaderIdx ? FalseWeight : TrueWeight;
  }

  // For each peeled-off iteration, make a copy of the loop.
  for (unsigned Iter = 0; Iter < PeelCount; ++Iter) {
    SmallVector<BasicBlock *, 8> NewBlocks;
    ValueToValueMapTy VMap;

    // The exit weight of the previous iteration is the header entry weight
    // of the current iteration. So this is exactly how many dynamic iterations
    // the current peeled-off static iteration uses up.
    // FIXME: due to the way the distribution is constructed, we need a
    // guard here to make sure we don't end up with non-positive weights.
    if (ExitWeight < BackEdgeWeight)
      BackEdgeWeight -= ExitWeight;
    else
      BackEdgeWeight = 1;

    cloneLoopBlocks(L, Iter, InsertTop, InsertBot, Exit,
                    NewBlocks, LoopBlocks, VMap, LVMap, LI);
    updateBranchWeights(InsertBot, cast<BranchInst>(VMap[LatchBR]), Iter,
                        PeelCount, ExitWeight);

    InsertTop = InsertBot;
    InsertBot = SplitBlock(InsertBot, InsertBot->getTerminator(), DT, LI);
    InsertBot->setName(Header->getName() + ".peel.next");

    F->getBasicBlockList().splice(InsertTop->getIterator(),
                                  F->getBasicBlockList(),
                                  NewBlocks[0]->getIterator(), F->end());

    // Remap to use values from the current iteration instead of the
    // previous one.
    remapInstructionsInBlocks(NewBlocks, VMap);
  }

  // Now adjust the phi nodes in the loop header to get their initial values
  // from the last peeled-off iteration instead of the preheader.
  for (BasicBlock::iterator I = Header->begin(); isa<PHINode>(I); ++I) {
    PHINode *PHI = cast<PHINode>(I);
    Value *NewVal = PHI->getIncomingValueForBlock(Latch);
    Instruction *LatchInst = dyn_cast<Instruction>(NewVal);
    if (LatchInst && L->contains(LatchInst))
      NewVal = LVMap[LatchInst];

    PHI->setIncomingValue(PHI->getBasicBlockIndex(NewPreHeader), NewVal);
  }

  // Adjust the branch weights on the loop exit.
  if (ExitWeight) {
    MDBuilder MDB(LatchBR->getContext());
    MDNode *WeightNode =
        HeaderIdx ? MDB.createBranchWeights(ExitWeight, BackEdgeWeight)
                  : MDB.createBranchWeights(BackEdgeWeight, ExitWeight);
    LatchBR->setMetadata(LLVMContext::MD_prof, WeightNode);
  }

  // If the loop is nested, we changed the parent loop, update SE.
  if (Loop *ParentLoop = L->getParentLoop())
    SE->forgetLoop(ParentLoop);

  NumPeeled++;

  return true;
}