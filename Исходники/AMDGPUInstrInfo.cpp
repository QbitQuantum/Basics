bool AMDGPUInstrInfo::expandPostRAPseudo (MachineBasicBlock::iterator MI) const {
  MachineBasicBlock *MBB = MI->getParent();

  switch(MI->getOpcode()) {
  default:
    if (isRegisterLoad(*MI)) {
      unsigned RegIndex = MI->getOperand(2).getImm();
      unsigned Channel = MI->getOperand(3).getImm();
      unsigned Address = calculateIndirectAddress(RegIndex, Channel);
      unsigned OffsetReg = MI->getOperand(1).getReg();
      if (OffsetReg == AMDGPU::INDIRECT_BASE_ADDR) {
        buildMovInstr(MBB, MI, MI->getOperand(0).getReg(),
                      getIndirectAddrRegClass()->getRegister(Address));
      } else {
        buildIndirectRead(MBB, MI, MI->getOperand(0).getReg(),
                          Address, OffsetReg);
      }
    } else if (isRegisterStore(*MI)) {
      unsigned RegIndex = MI->getOperand(2).getImm();
      unsigned Channel = MI->getOperand(3).getImm();
      unsigned Address = calculateIndirectAddress(RegIndex, Channel);
      unsigned OffsetReg = MI->getOperand(1).getReg();
      if (OffsetReg == AMDGPU::INDIRECT_BASE_ADDR) {
        buildMovInstr(MBB, MI, getIndirectAddrRegClass()->getRegister(Address),
                      MI->getOperand(0).getReg());
      } else {
        buildIndirectWrite(MBB, MI, MI->getOperand(0).getReg(),
                         calculateIndirectAddress(RegIndex, Channel),
                         OffsetReg);
      }
    } else {
      return false;
    }
  }

  MBB->erase(MI);
  return true;
}