bool MipsInstrInfo::expandPostRAPseudo(MachineBasicBlock::iterator MI) const {
  MachineBasicBlock &MBB = *MI->getParent();

  switch(MI->getDesc().getOpcode()) {
  default:
    return false;
  case Mips::BuildPairF64:
    ExpandBuildPairF64(MBB, MI);
    break;
  case Mips::ExtractElementF64:
    ExpandExtractElementF64(MBB, MI);
    break;
  }

  MBB.erase(MI);
  return true;
}