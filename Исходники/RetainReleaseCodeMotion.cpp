void ReleaseCodeMotionContext::computeCodeMotionInsertPoints() {
  // The BBSetIns have converged, run last iteration and figure out insertion
  // point for each RC root.
  for (SILBasicBlock *BB : PO->getPostOrder()) {
    // Intersect in the successor BBSetIns.
    mergeBBDataFlowStates(BB);
    ReleaseBlockState *S = BlockStates[BB];

    // Compute insertion point generated by the edge value transition.
    // If there is a transition from 1 to 0, that means we have a partial
    // merge, which means the release can NOT be hoisted to the current block.
    // place it at the successors.
    for (unsigned i = 0; i < RCRootVault.size(); ++i) {  
      if (S->BBSetOut[i])
        continue;
      for (auto &Succ : BB->getSuccessors()) {
        BlockState *SBB = BlockStates[Succ];
        if (!SBB->BBSetIn[i])
          continue;
        InsertPoints[RCRootVault[i]].push_back(&*(*Succ).begin());
      }
    }

    // Is this block interesting ?
    if (MultiIteration && !InterestBlocks.count(BB))
      continue;

    // Compute insertion point generated by MayUse terminator inst.
    // If terminator instruction can block the RC root. We will have no
    // choice but to anchor the release instructions in the successor blocks.
    for (unsigned i = 0; i < RCRootVault.size(); ++i) {
      SILInstruction *Term = BB->getTerminator();
      if (!S->BBSetOut[i] || !mayBlockCodeMotion(Term, RCRootVault[i]))
        continue;
      for (auto &Succ : BB->getSuccessors()) {
        BlockState *SBB = BlockStates[Succ];
        if (!SBB->BBSetIn[i])
          continue;
        InsertPoints[RCRootVault[i]].push_back(&*(*Succ).begin());
      }
      S->BBSetOut.reset(i);
    }

    // Compute insertion point generated within the basic block. Process
    // instructions in post-order fashion.
    for (auto I = std::next(BB->rbegin()), E = BB->rend(); I != E; ++I) {
      for (unsigned i = 0; i < RCRootVault.size(); ++i) {
        if (!S->BBSetOut[i] || !mayBlockCodeMotion(&*I, RCRootVault[i]))
          continue;
        auto *InsertPt = &*std::next(SILBasicBlock::iterator(&*I));
        InsertPoints[RCRootVault[i]].push_back(InsertPt);
        S->BBSetOut.reset(i);
      }

      // If we are freezing this epilogue release. Simply continue.
      if (FreezeEpilogueReleases && ERM.isEpilogueRelease(&*I))
        continue;

      // This release generates.
      if (isReleaseInstruction(&*I)) {
        S->BBSetOut.set(RCRootIndex[getRCRoot(&*I)]);
      }
    }

    // Compute insertion point generated by SILArgument. SILArgument blocks if
    // it defines the released value.
    for (unsigned i = 0; i < RCRootVault.size(); ++i) {
      if (!S->BBSetOut[i]) 
        continue;
      SILArgument *A = dyn_cast<SILArgument>(RCRootVault[i]);
      if (!A || A->getParent() != BB)
        continue;
      InsertPoints[RCRootVault[i]].push_back(&*BB->begin());
      S->BBSetOut.reset(i);
    }
   
    // Lastly update the BBSetIn, only necessary when we are running a single
    // iteration dataflow.
    if (!MultiIteration) {
      S->updateBBSetIn(S->BBSetOut);
    }
  }
}