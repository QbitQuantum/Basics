bool AArch64FrameLowering::restoreCalleeSavedRegisters(
    MachineBasicBlock &MBB, MachineBasicBlock::iterator MI,
    const std::vector<CalleeSavedInfo> &CSI,
    const TargetRegisterInfo *TRI) const {
  MachineFunction &MF = *MBB.getParent();
  const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
  unsigned Count = CSI.size();
  DebugLoc DL;
  assert((Count & 1) == 0 && "Odd number of callee-saved regs to spill!");

  if (MI != MBB.end())
    DL = MI->getDebugLoc();

  for (unsigned i = 0; i < Count; i += 2) {
    unsigned Reg1 = CSI[i].getReg();
    unsigned Reg2 = CSI[i + 1].getReg();
    // GPRs and FPRs are saved in pairs of 64-bit regs. We expect the CSI
    // list to come in sorted by frame index so that we can issue the store
    // pair instructions directly. Assert if we see anything otherwise.
    assert(CSI[i].getFrameIdx() + 1 == CSI[i + 1].getFrameIdx() &&
           "Out of order callee saved regs!");
    // Issue sequence of non-sp increment and sp-pi restores for cs regs. Only
    // the last load is sp-pi post-increment and de-allocates the stack:
    // For example:
    //    ldp     fp, lr, [sp, #32]       // addImm(+4)
    //    ldp     x20, x19, [sp, #16]     // addImm(+2)
    //    ldp     x22, x21, [sp], #48     // addImm(+6)
    // Note: see comment in spillCalleeSavedRegisters()
    unsigned LdrOpc;

    assert((Count & 1) == 0 && "Odd number of callee-saved regs to spill!");
    assert((i & 1) == 0 && "Odd index for callee-saved reg spill!");
    if (AArch64::GPR64RegClass.contains(Reg1)) {
      assert(AArch64::GPR64RegClass.contains(Reg2) &&
             "Expected GPR64 callee-saved register pair!");
      if (i == Count - 2)
        LdrOpc = AArch64::LDPXpost;
      else
        LdrOpc = AArch64::LDPXi;
    } else if (AArch64::FPR64RegClass.contains(Reg1)) {
      assert(AArch64::FPR64RegClass.contains(Reg2) &&
             "Expected FPR64 callee-saved register pair!");
      if (i == Count - 2)
        LdrOpc = AArch64::LDPDpost;
      else
        LdrOpc = AArch64::LDPDi;
    } else
      llvm_unreachable("Unexpected callee saved register!");
    DEBUG(dbgs() << "CSR restore: (" << TRI->getName(Reg1) << ", "
                 << TRI->getName(Reg2) << ") -> fi#(" << CSI[i].getFrameIdx()
                 << ", " << CSI[i + 1].getFrameIdx() << ")\n");

    // Compute offset: i = 0 => offset = Count - 2; i = 2 => offset = Count - 4;
    // etc.
    const int Offset = (i == Count - 2) ? Count : Count - i - 2;
    assert((Offset >= -64 && Offset <= 63) &&
           "Offset out of bounds for LDP immediate");
    MachineInstrBuilder MIB = BuildMI(MBB, MI, DL, TII.get(LdrOpc));
    if (LdrOpc == AArch64::LDPXpost || LdrOpc == AArch64::LDPDpost)
      MIB.addReg(AArch64::SP, RegState::Define);

    MIB.addReg(Reg2, getDefRegState(true))
        .addReg(Reg1, getDefRegState(true))
        .addReg(AArch64::SP)
        .addImm(Offset); // [sp], #offset * 8  or [sp, #offset * 8]
                         // where the factor * 8 is implicit
  }
  return true;
}