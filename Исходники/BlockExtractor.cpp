/// Extracts the landing pads to make sure all of them have only one
/// predecessor.
void BlockExtractor::splitLandingPadPreds(Function &F) {
  for (BasicBlock &BB : F) {
    for (Instruction &I : BB) {
      if (!isa<InvokeInst>(&I))
        continue;
      InvokeInst *II = cast<InvokeInst>(&I);
      BasicBlock *Parent = II->getParent();
      BasicBlock *LPad = II->getUnwindDest();

      // Look through the landing pad's predecessors. If one of them ends in an
      // 'invoke', then we want to split the landing pad.
      bool Split = false;
      for (auto PredBB : predecessors(LPad)) {
        if (PredBB->isLandingPad() && PredBB != Parent &&
            isa<InvokeInst>(Parent->getTerminator())) {
          Split = true;
          break;
        }
      }

      if (!Split)
        continue;

      SmallVector<BasicBlock *, 2> NewBBs;
      SplitLandingPadPredecessors(LPad, Parent, ".1", ".2", NewBBs);
    }
  }
}