/// Handle the direct use of a physical register.  Check that the register is
/// not used by a virtreg. Kill the physreg, marking it free. This may add
/// implicit kills to MO->getParent() and invalidate MO.
void RegAllocFast::usePhysReg(MachineOperand &MO) {
  // Ignore undef uses.
  if (MO.isUndef())
    return;

  unsigned PhysReg = MO.getReg();
  assert(TargetRegisterInfo::isPhysicalRegister(PhysReg) &&
         "Bad usePhysReg operand");

  markRegUsedInInstr(PhysReg);
  switch (PhysRegState[PhysReg]) {
  case regDisabled:
    break;
  case regReserved:
    PhysRegState[PhysReg] = regFree;
    LLVM_FALLTHROUGH;
  case regFree:
    MO.setIsKill();
    return;
  default:
    // The physreg was allocated to a virtual register. That means the value we
    // wanted has been clobbered.
    llvm_unreachable("Instruction uses an allocated register");
  }

  // Maybe a superregister is reserved?
  for (MCRegAliasIterator AI(PhysReg, TRI, false); AI.isValid(); ++AI) {
    MCPhysReg Alias = *AI;
    switch (PhysRegState[Alias]) {
    case regDisabled:
      break;
    case regReserved:
      // Either PhysReg is a subregister of Alias and we mark the
      // whole register as free, or PhysReg is the superregister of
      // Alias and we mark all the aliases as disabled before freeing
      // PhysReg.
      // In the latter case, since PhysReg was disabled, this means that
      // its value is defined only by physical sub-registers. This check
      // is performed by the assert of the default case in this loop.
      // Note: The value of the superregister may only be partial
      // defined, that is why regDisabled is a valid state for aliases.
      assert((TRI->isSuperRegister(PhysReg, Alias) ||
              TRI->isSuperRegister(Alias, PhysReg)) &&
             "Instruction is not using a subregister of a reserved register");
      LLVM_FALLTHROUGH;
    case regFree:
      if (TRI->isSuperRegister(PhysReg, Alias)) {
        // Leave the superregister in the working set.
        setPhysRegState(Alias, regFree);
        MO.getParent()->addRegisterKilled(Alias, TRI, true);
        return;
      }
      // Some other alias was in the working set - clear it.
      setPhysRegState(Alias, regDisabled);
      break;
    default:
      llvm_unreachable("Instruction uses an alias of an allocated register");
    }
  }

  // All aliases are disabled, bring register into working set.
  setPhysRegState(PhysReg, regFree);
  MO.setIsKill();
}