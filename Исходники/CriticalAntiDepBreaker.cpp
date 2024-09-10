// Check all machine operands that reference the antidependent register and must
// be replaced by NewReg. Return true if any of their parent instructions may
// clobber the new register.
//
// Note: AntiDepReg may be referenced by a two-address instruction such that
// it's use operand is tied to a def operand. We guard against the case in which
// the two-address instruction also defines NewReg, as may happen with
// pre/postincrement loads. In this case, both the use and def operands are in
// RegRefs because the def is inserted by PrescanInstruction and not erased
// during ScanInstruction. So checking for an instructions with definitions of
// both NewReg and AntiDepReg covers it.
bool
CriticalAntiDepBreaker::isNewRegClobberedByRefs(RegRefIter RegRefBegin,
                                                RegRefIter RegRefEnd,
                                                unsigned NewReg)
{
  for (RegRefIter I = RegRefBegin; I != RegRefEnd; ++I ) {
    MachineOperand *RefOper = I->second;

    // Don't allow the instruction defining AntiDepReg to earlyclobber its
    // operands, in case they may be assigned to NewReg. In this case antidep
    // breaking must fail, but it's too rare to bother optimizing.
    if (RefOper->isDef() && RefOper->isEarlyClobber())
      return true;

    // Handle cases in which this instructions defines NewReg.
    MachineInstr *MI = RefOper->getParent();
    for (unsigned i = 0, e = MI->getNumOperands(); i != e; ++i) {
      const MachineOperand &CheckOper = MI->getOperand(i);

      if (CheckOper.isRegMask() && CheckOper.clobbersPhysReg(NewReg))
        return true;

      if (!CheckOper.isReg() || !CheckOper.isDef() ||
          CheckOper.getReg() != NewReg)
        continue;

      // Don't allow the instruction to define NewReg and AntiDepReg.
      // When AntiDepReg is renamed it will be an illegal op.
      if (RefOper->isDef())
        return true;

      // Don't allow an instruction using AntiDepReg to be earlyclobbered by
      // NewReg
      if (CheckOper.isEarlyClobber())
        return true;

      // Don't allow inline asm to define NewReg at all. Who know what it's
      // doing with it.
      if (MI->isInlineAsm())
        return true;
    }
  }
  return false;
}