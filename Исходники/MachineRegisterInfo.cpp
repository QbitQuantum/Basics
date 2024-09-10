void MachineRegisterInfo::verifyUseList(unsigned Reg) const {
#ifndef NDEBUG
  bool Valid = true;
  for (MachineOperand &M : reg_operands(Reg)) {
    MachineOperand *MO = &M;
    MachineInstr *MI = MO->getParent();
    if (!MI) {
      errs() << PrintReg(Reg, getTargetRegisterInfo())
             << " use list MachineOperand " << MO
             << " has no parent instruction.\n";
      Valid = false;
      continue;
    }
    MachineOperand *MO0 = &MI->getOperand(0);
    unsigned NumOps = MI->getNumOperands();
    if (!(MO >= MO0 && MO < MO0+NumOps)) {
      errs() << PrintReg(Reg, getTargetRegisterInfo())
             << " use list MachineOperand " << MO
             << " doesn't belong to parent MI: " << *MI;
      Valid = false;
    }
    if (!MO->isReg()) {
      errs() << PrintReg(Reg, getTargetRegisterInfo())
             << " MachineOperand " << MO << ": " << *MO
             << " is not a register\n";
      Valid = false;
    }
    if (MO->getReg() != Reg) {
      errs() << PrintReg(Reg, getTargetRegisterInfo())
             << " use-list MachineOperand " << MO << ": "
             << *MO << " is the wrong register\n";
      Valid = false;
    }
  }
  assert(Valid && "Invalid use list");
#endif
}