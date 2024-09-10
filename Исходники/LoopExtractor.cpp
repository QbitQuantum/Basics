/// SplitLandingPadPreds - The landing pad needs to be extracted with the invoke
/// instruction. The critical edge breaker will refuse to break critical edges
/// to a landing pad. So do them here. After this method runs, all landing pads
/// should have only one predecessor.
void BlockExtractorPass::SplitLandingPadPreds(Function *F) {
  for (Function::iterator I = F->begin(), E = F->end(); I != E; ++I) {
    InvokeInst *II = dyn_cast<InvokeInst>(I);
    if (!II) continue;
    BasicBlock *Parent = II->getParent();
    BasicBlock *LPad = II->getUnwindDest();

    // Look through the landing pad's predecessors. If one of them ends in an
    // 'invoke', then we want to split the landing pad.
    bool Split = false;
    for (pred_iterator
           PI = pred_begin(LPad), PE = pred_end(LPad); PI != PE; ++PI) {
      BasicBlock *BB = *PI;
      if (BB->isLandingPad() && BB != Parent &&
          isa<InvokeInst>(Parent->getTerminator())) {
        Split = true;
        break;
      }
    }

    if (!Split) continue;

    SmallVector<BasicBlock*, 2> NewBBs;
    SplitLandingPadPredecessors(LPad, Parent, ".1", ".2", NewBBs);
  }
}