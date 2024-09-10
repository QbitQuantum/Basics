MachineBasicBlock::iterator
X86InstrInfo::reverseBranchCondition(MachineBasicBlock::iterator MI) const {
  unsigned Opcode = MI->getOpcode();
  assert(isBranch(Opcode) && "MachineInstr must be a branch");
  unsigned ROpcode;
  switch (Opcode) {
  default: assert(0 && "Cannot reverse unconditional branches!");
  case X86::JB:  ROpcode = X86::JAE; break;
  case X86::JAE: ROpcode = X86::JB;  break;
  case X86::JE:  ROpcode = X86::JNE; break;
  case X86::JNE: ROpcode = X86::JE;  break;
  case X86::JBE: ROpcode = X86::JA;  break;
  case X86::JA:  ROpcode = X86::JBE; break;
  case X86::JS:  ROpcode = X86::JNS; break;
  case X86::JNS: ROpcode = X86::JS;  break;
  case X86::JL:  ROpcode = X86::JGE; break;
  case X86::JGE: ROpcode = X86::JL;  break;
  case X86::JLE: ROpcode = X86::JG;  break;
  case X86::JG:  ROpcode = X86::JLE; break;
  }
  MachineBasicBlock* MBB = MI->getParent();
  MachineBasicBlock* TMBB = MI->getOperand(0).getMachineBasicBlock();
  return BuildMI(*MBB, MBB->erase(MI), ROpcode, 1).addMBB(TMBB);
}