bool LibCallAliasAnalysis::runOnFunction(Function &F) {
  // set up super class
  InitializeAliasAnalysis(this, &F.getParent()->getDataLayout());
  return false;
}