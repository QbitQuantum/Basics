bool Mips16InstrInfo::expandPostRAPseudo(MachineBasicBlock::iterator MI) const {
  MachineBasicBlock &MBB = *MI->getParent();

  switch(MI->getDesc().getOpcode()) {
  default:
    return false;
  case Mips::RetRA16:
    ExpandRetRA16(MBB, MI, Mips::JrRa16);
    break;
  }

  MBB.erase(MI);
  return true;
}