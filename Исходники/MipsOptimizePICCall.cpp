bool OptimizePICCall::isCallViaRegister(MachineInstr &MI, unsigned &Reg,
                                        ValueType &Val) const {
  if (!MI.isCall())
    return false;

  MachineOperand *MO = getCallTargetRegOpnd(MI);

  // Return if MI is not a function call via a register.
  if (!MO)
    return false;

  // Get the instruction that loads the function address from the GOT.
  Reg = MO->getReg();
  Val = (Value*)nullptr;
  MachineRegisterInfo &MRI = MI.getParent()->getParent()->getRegInfo();
  MachineInstr *DefMI = MRI.getVRegDef(Reg);

  assert(DefMI);

  // See if DefMI is an instruction that loads from a GOT entry that holds the
  // address of a lazy binding stub.
  if (!DefMI->mayLoad() || DefMI->getNumOperands() < 3)
    return true;

  unsigned Flags = DefMI->getOperand(2).getTargetFlags();

  if (Flags != MipsII::MO_GOT_CALL && Flags != MipsII::MO_CALL_LO16)
    return true;

  // Return the underlying object for the GOT entry in Val.
  assert(DefMI->hasOneMemOperand());
  Val = (*DefMI->memoperands_begin())->getValue();
  if (!Val)
    Val = (*DefMI->memoperands_begin())->getPseudoValue();
  return true;
}