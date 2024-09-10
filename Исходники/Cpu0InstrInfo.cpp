// Cpu0InstrInfo::expandPostRAPseudo
/// Expand Pseudo instructions into real backend instructions
bool Cpu0InstrInfo::expandPostRAPseudo(MachineBasicBlock::iterator MI) const {
  MachineBasicBlock &MBB = *MI->getParent();

  switch(MI->getDesc().getOpcode()) {
  default:
    return false;
  case Cpu0::RetLR:
    ExpandRetLR(MBB, MI, Cpu0::RET);
    break;
  }

  MBB.erase(MI);
  return true;
}