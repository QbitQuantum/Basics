// Compare compares the result of MI against zero.  If MI is a suitable load
// instruction and if CCUsers is a single conditional trap on zero, eliminate
// the load and convert the branch to a load-and-trap.  Return true on success.
bool SystemZElimCompare::convertToLoadAndTrap(
    MachineInstr &MI, MachineInstr &Compare,
    SmallVectorImpl<MachineInstr *> &CCUsers) {
  unsigned LATOpcode = TII->getLoadAndTrap(MI.getOpcode());
  if (!LATOpcode)
    return false;

  // Check whether we have a single CondTrap that traps on zero.
  if (CCUsers.size() != 1)
    return false;
  MachineInstr *Branch = CCUsers[0];
  if (Branch->getOpcode() != SystemZ::CondTrap ||
      Branch->getOperand(0).getImm() != SystemZ::CCMASK_ICMP ||
      Branch->getOperand(1).getImm() != SystemZ::CCMASK_CMP_EQ)
    return false;

  // We already know that there are no references to the register between
  // MI and Compare.  Make sure that there are also no references between
  // Compare and Branch.
  unsigned SrcReg = getCompareSourceReg(Compare);
  MachineBasicBlock::iterator MBBI = Compare, MBBE = Branch;
  for (++MBBI; MBBI != MBBE; ++MBBI)
    if (getRegReferences(*MBBI, SrcReg))
      return false;

  // The transformation is OK.  Rebuild Branch as a load-and-trap.
  while (Branch->getNumOperands())
    Branch->RemoveOperand(0);
  Branch->setDesc(TII->get(LATOpcode));
  MachineInstrBuilder(*Branch->getParent()->getParent(), Branch)
      .addOperand(MI.getOperand(0))
      .addOperand(MI.getOperand(1))
      .addOperand(MI.getOperand(2))
      .addOperand(MI.getOperand(3));
  MI.eraseFromParent();
  return true;
}