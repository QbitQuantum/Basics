void HexagonCopyToCombine::emitCombineIR(MachineBasicBlock::iterator &InsertPt,
                                         unsigned DoubleDestReg,
                                         MachineOperand &HiOperand,
                                         MachineOperand &LoOperand) {
  unsigned LoReg = LoOperand.getReg();
  unsigned LoRegKillFlag = getKillRegState(LoOperand.isKill());

  DebugLoc DL = InsertPt->getDebugLoc();
  MachineBasicBlock *BB = InsertPt->getParent();

  // Handle global.
  if (HiOperand.isGlobal()) {
    BuildMI(*BB, InsertPt, DL, TII->get(Hexagon::A4_combineir), DoubleDestReg)
      .addGlobalAddress(HiOperand.getGlobal(), HiOperand.getOffset(),
                        HiOperand.getTargetFlags())
      .addReg(LoReg, LoRegKillFlag);
    return;
  }
  // Insert new combine instruction.
  //  DoubleRegDest = combine #HiImm, LoReg
  BuildMI(*BB, InsertPt, DL, TII->get(Hexagon::A4_combineir), DoubleDestReg)
    .addImm(HiOperand.getImm())
    .addReg(LoReg, LoRegKillFlag);
}