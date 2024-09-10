/// Generate a conditional transfer, copying the value SrcOp to the
/// destination register DstR:DstSR, and using the predicate register from
/// PredOp. The Cond argument specifies whether the predicate is to be
/// if(PredOp), or if(!PredOp).
MachineInstr *HexagonExpandCondsets::genTfrFor(MachineOperand &SrcOp,
      unsigned DstR, unsigned DstSR, const MachineOperand &PredOp, bool Cond) {
  MachineInstr *MI = SrcOp.getParent();
  MachineBasicBlock &B = *MI->getParent();
  MachineBasicBlock::iterator At = MI;
  DebugLoc DL = MI->getDebugLoc();

  // Don't avoid identity copies here (i.e. if the source and the destination
  // are the same registers). It is actually better to generate them here,
  // since this would cause the copy to potentially be predicated in the next
  // step. The predication will remove such a copy if it is unable to
  /// predicate.

  unsigned Opc = getCondTfrOpcode(SrcOp, Cond);
  MachineInstr *TfrI = BuildMI(B, At, DL, HII->get(Opc))
        .addReg(DstR, RegState::Define, DstSR)
        .addOperand(PredOp)
        .addOperand(SrcOp);
  // We don't want any kills yet.
  TfrI->clearKillInfo();
  DEBUG(dbgs() << "created an initial copy: " << *TfrI);
  return TfrI;
}