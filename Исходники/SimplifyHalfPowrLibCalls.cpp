/// runOnFunction - Top level algorithm.
///
bool SimplifyHalfPowrLibCalls::runOnFunction(Function &F) {
  TD = getAnalysisIfAvailable<TargetData>();
  
  bool Changed = false;
  std::vector<Instruction *> HalfPowrs;
  for (Function::iterator BB = F.begin(), E = F.end(); BB != E; ++BB) {
    for (BasicBlock::iterator I = BB->begin(), E = BB->end(); I != E; ++I) {
      // Look for calls.
      bool IsHalfPowr = false;
      if (CallInst *CI = dyn_cast<CallInst>(I)) {
        // Look for direct calls and calls to non-external functions.
        Function *Callee = CI->getCalledFunction();
        if (Callee && Callee->hasExternalLinkage()) {
          // Look for calls with well-known names.
          if (Callee->getName() == "__half_powrf4")
            IsHalfPowr = true;
        }
      }
      if (IsHalfPowr)
        HalfPowrs.push_back(I);
      // We're looking for sequences of up to three such calls, which we'll
      // simplify as a group.
      if ((!IsHalfPowr && !HalfPowrs.empty()) || HalfPowrs.size() == 3) {
        I = InlineHalfPowrs(HalfPowrs, I);
        E = I->getParent()->end();
        HalfPowrs.clear();
        Changed = true;
      }
    }
    assert(HalfPowrs.empty() && "Block had no terminator!");
  }

  return Changed;
}