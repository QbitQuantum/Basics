LaneBitmask DetectDeadLanes::transferDefinedLanes(const MachineOperand &Def,
    unsigned OpNum, LaneBitmask DefinedLanes) const {
  const MachineInstr &MI = *Def.getParent();
  // Translate DefinedLanes if necessary.
  switch (MI.getOpcode()) {
  case TargetOpcode::REG_SEQUENCE: {
    unsigned SubIdx = MI.getOperand(OpNum + 1).getImm();
    DefinedLanes = TRI->composeSubRegIndexLaneMask(SubIdx, DefinedLanes);
    DefinedLanes &= TRI->getSubRegIndexLaneMask(SubIdx);
    break;
  }
  case TargetOpcode::INSERT_SUBREG: {
    unsigned SubIdx = MI.getOperand(3).getImm();
    if (OpNum == 2) {
      DefinedLanes = TRI->composeSubRegIndexLaneMask(SubIdx, DefinedLanes);
      DefinedLanes &= TRI->getSubRegIndexLaneMask(SubIdx);
    } else {
      assert(OpNum == 1 && "INSERT_SUBREG must have two operands");
      // Ignore lanes defined by operand 2.
      DefinedLanes &= ~TRI->getSubRegIndexLaneMask(SubIdx);
    }
    break;
  }
  case TargetOpcode::EXTRACT_SUBREG: {
    unsigned SubIdx = MI.getOperand(2).getImm();
    assert(OpNum == 1 && "EXTRACT_SUBREG must have one register operand only");
    DefinedLanes = TRI->reverseComposeSubRegIndexLaneMask(SubIdx, DefinedLanes);
    break;
  }
  case TargetOpcode::COPY:
  case TargetOpcode::PHI:
    break;
  default:
    llvm_unreachable("function must be called with COPY-like instruction");
  }

  assert(Def.getSubReg() == 0 &&
         "Should not have subregister defs in machine SSA phase");
  DefinedLanes &= MRI->getMaxLaneMaskForVReg(Def.getReg());
  return DefinedLanes;
}