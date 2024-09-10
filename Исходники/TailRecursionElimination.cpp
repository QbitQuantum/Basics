bool TailCallElim::FoldReturnAndProcessPred(BasicBlock *BB,
                                       ReturnInst *Ret, BasicBlock *&OldEntry,
                                       bool &TailCallsAreMarkedTail,
                                       SmallVectorImpl<PHINode *> &ArgumentPHIs,
                                       bool CannotTailCallElimCallsMarkedTail) {
  bool Change = false;

  // If the return block contains nothing but the return and PHI's,
  // there might be an opportunity to duplicate the return in its
  // predecessors and perform TRC there. Look for predecessors that end
  // in unconditional branch and recursive call(s).
  SmallVector<BranchInst*, 8> UncondBranchPreds;
  for (pred_iterator PI = pred_begin(BB), E = pred_end(BB); PI != E; ++PI) {
    BasicBlock *Pred = *PI;
    TerminatorInst *PTI = Pred->getTerminator();
    if (BranchInst *BI = dyn_cast<BranchInst>(PTI))
      if (BI->isUnconditional())
        UncondBranchPreds.push_back(BI);
  }

  while (!UncondBranchPreds.empty()) {
    BranchInst *BI = UncondBranchPreds.pop_back_val();
    BasicBlock *Pred = BI->getParent();
    if (CallInst *CI = FindTRECandidate(BI, CannotTailCallElimCallsMarkedTail)){
      DEBUG(dbgs() << "FOLDING: " << *BB
            << "INTO UNCOND BRANCH PRED: " << *Pred);
      EliminateRecursiveTailCall(CI, FoldReturnIntoUncondBranch(Ret, BB, Pred),
                                 OldEntry, TailCallsAreMarkedTail, ArgumentPHIs,
                                 CannotTailCallElimCallsMarkedTail);
      ++NumRetDuped;
      Change = true;
    }
  }

  return Change;
}