/// Terminate all open ranges at the end of the current basic block.
bool LiveDebugValues::transferTerminatorInst(MachineInstr &MI,
                                             VarLocList &OpenRanges,
                                             VarLocInMBB &OutLocs) {
  bool Changed = false;
  const MachineBasicBlock *CurMBB = MI.getParent();
  if (!(MI.isTerminator() || (&MI == &CurMBB->instr_back())))
    return false;

  if (OpenRanges.empty())
    return false;

  VarLocList &VLL = OutLocs[CurMBB];

  for (auto OR : OpenRanges) {
    // Copy OpenRanges to OutLocs, if not already present.
    assert(OR.MI->isDebugValue());
    DEBUG(dbgs() << "Add to OutLocs: "; OR.MI->dump(););
    if (std::find_if(VLL.begin(), VLL.end(),
                     [&](const VarLoc &V) { return (OR == V); }) == VLL.end()) {
      VLL.push_back(std::move(OR));
      Changed = true;
    }
  }