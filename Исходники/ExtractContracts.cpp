void ExtractContracts::validateAnnotation(CallInst &I) {
  assert(I.getCalledFunction() && "Unexpected virtual function.");
  assert(I.getNumArgOperands() == 1 && "Unexpected operands.");
  auto B = I.getParent();
  auto F = B->getParent();
  auto& DT = getAnalysis<DominatorTreeWrapperPass>(*F).getDomTree();
  auto& LI = getAnalysis<LoopInfoWrapperPass>(*F).getLoopInfo();
  if (I.getCalledFunction()->getName() == Naming::CONTRACT_INVARIANT) {
    auto L = LI[B];
    if (!L) {
      llvm_unreachable("Loop invariants must occur inside loops.");
    }
  } else {
    for (auto L : LI) {
      auto& J = L->getHeader()->getInstList().front();
      if (DT.dominates(&J, &I)) {
        llvm_unreachable("Procedure specifications must occur before loops.");
      }
    }
  }
}