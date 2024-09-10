static bool isKUImmOperand(const SIInstrInfo *TII, const MachineOperand &Src) {
  return isUInt<16>(Src.getImm()) &&
    !TII->isInlineConstant(*Src.getParent(),
                           Src.getParent()->getOperandNo(&Src));
}