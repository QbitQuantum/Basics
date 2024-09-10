bool InstructionSelector::constrainSelectedInstRegOperands(
    MachineInstr &I, const TargetInstrInfo &TII, const TargetRegisterInfo &TRI,
    const RegisterBankInfo &RBI) const {
  MachineBasicBlock &MBB = *I.getParent();
  MachineFunction &MF = *MBB.getParent();
  MachineRegisterInfo &MRI = MF.getRegInfo();

  for (unsigned OpI = 0, OpE = I.getNumExplicitOperands(); OpI != OpE; ++OpI) {
    MachineOperand &MO = I.getOperand(OpI);

    // There's nothing to be done on non-register operands.
    if (!MO.isReg())
      continue;

    DEBUG(dbgs() << "Converting operand: " << MO << '\n');
    assert(MO.isReg() && "Unsupported non-reg operand");

    // Physical registers don't need to be constrained.
    if (TRI.isPhysicalRegister(MO.getReg()))
      continue;

    const TargetRegisterClass *RC = TII.getRegClass(I.getDesc(), OpI, &TRI, MF);
    assert(RC && "Selected inst should have regclass operand");

    // If the operand is a vreg, we should constrain its regclass, and only
    // insert COPYs if that's impossible.
    // If the operand is a physreg, we only insert COPYs if the register class
    // doesn't contain the register.
    if (RBI.constrainGenericRegister(MO.getReg(), *RC, MRI))
      continue;

    DEBUG(dbgs() << "Constraining with COPYs isn't implemented yet");
    return false;
  }
  return true;
}