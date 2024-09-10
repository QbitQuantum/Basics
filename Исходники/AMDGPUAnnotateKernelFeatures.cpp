void AMDGPUAnnotateKernelFeatures::addAttrToCallers(Function *Intrin,
                                                    StringRef AttrName) {
  SmallPtrSet<Function *, 4> SeenFuncs;

  for (User *U : Intrin->users()) {
    // CallInst is the only valid user for an intrinsic.
    CallInst *CI = cast<CallInst>(U);

    Function *CallingFunction = CI->getParent()->getParent();
    if (SeenFuncs.insert(CallingFunction).second)
      CallingFunction->addFnAttr(AttrName);
  }
}