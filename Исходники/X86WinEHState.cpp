// Calculate the state a call-site is in.
static int getStateForCallSite(DenseMap<BasicBlock *, ColorVector> &BlockColors,
                               WinEHFuncInfo &FuncInfo, CallSite CS) {
  if (auto *II = dyn_cast<InvokeInst>(CS.getInstruction())) {
    // Look up the state number of the EH pad this unwinds to.
    assert(FuncInfo.InvokeStateMap.count(II) && "invoke has no state!");
    return FuncInfo.InvokeStateMap[II];
  }
  // Possibly throwing call instructions have no actions to take after
  // an unwind. Ensure they are in the -1 state.
  return getBaseStateForBB(BlockColors, FuncInfo, CS.getParent());
}