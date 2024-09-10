/// Extract in a new basic block the omp fork call
int SplitOMPCall(Module *mod, Function *F, Pass *P, std::string RegionName) {
  std::string functionCall;
  int t = 0;

  CallInst *iFirst;
  Instruction *iSecond;

  // XXX To optimize with a single run trough the instructions
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
    if (t) {
      Instruction *instru = dyn_cast<Instruction>(&*I);
      iSecond = instru;
      break;
    }
    if (CallInst *callInst = dyn_cast<CallInst>(&*I)) {
      if (callInst->getCalledFunction()) {
        functionCall = callInst->getCalledFunction()->getName();
        if (ChooseExtract(functionCall, RegionName, callInst, F)) {
          t = 1;
          iFirst = callInst;
        }
      }
    }
  }
  if (t) {
    SplitBlock(iFirst->getParent(), iFirst, P);
    SplitBlock(iSecond->getParent(), iSecond, P);
  }

  return t;
}