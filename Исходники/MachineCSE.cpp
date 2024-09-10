bool MachineCSE::PerformTrivialCoalescing(MachineInstr *MI,
                                          MachineBasicBlock *MBB) {
  bool Changed = false;
  for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
    MachineOperand &MO = MI->getOperand(i);
    if (!MO.isReg() || !MO.isUse())
      continue;
    unsigned Reg = MO.getReg();
    if (!TargetRegisterInfo::isVirtualRegister(Reg))
      continue;
    if (!MRI->hasOneNonDBGUse(Reg))
      // Only coalesce single use copies. This ensure the copy will be
      // deleted.
      continue;
    MachineInstr *DefMI = MRI->getVRegDef(Reg);
    if (DefMI->getParent() != MBB)
      continue;
    if (!DefMI->isCopy())
      continue;
    unsigned SrcReg = DefMI->getOperand(1).getReg();
    if (!TargetRegisterInfo::isVirtualRegister(SrcReg))
      continue;
    if (DefMI->getOperand(0).getSubReg() || DefMI->getOperand(1).getSubReg())
      continue;
    if (!MRI->constrainRegClass(SrcReg, MRI->getRegClass(Reg)))
      continue;
    DEBUG(dbgs() << "Coalescing: " << *DefMI);
    DEBUG(dbgs() << "***     to: " << *MI);
    MO.setReg(SrcReg);
    MRI->clearKillFlags(SrcReg);
    DefMI->eraseFromParent();
    ++NumCoalesces;
    Changed = true;
  }

  return Changed;
}