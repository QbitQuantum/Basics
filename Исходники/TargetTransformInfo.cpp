TargetIRAnalysis::Result TargetIRAnalysis::getDefaultTTI(const Function &F) {
  return Result(F.getParent()->getDataLayout());
}