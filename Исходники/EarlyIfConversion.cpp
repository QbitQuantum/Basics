/// canSpeculateInstrs - Returns true if all the instructions in MBB can safely
/// be speculated. The terminators are not considered.
///
/// If instructions use any values that are defined in the head basic block,
/// the defining instructions are added to InsertAfter.
///
/// Any clobbered regunits are added to ClobberedRegUnits.
///
bool SSAIfConv::canSpeculateInstrs(MachineBasicBlock *MBB) {
  // Reject any live-in physregs. It's probably CPSR/EFLAGS, and very hard to
  // get right.
  if (!MBB->livein_empty()) {
    DEBUG(dbgs() << "BB#" << MBB->getNumber() << " has live-ins.\n");
    return false;
  }

  unsigned InstrCount = 0;

  // Check all instructions, except the terminators. It is assumed that
  // terminators never have side effects or define any used register values.
  for (MachineBasicBlock::iterator I = MBB->begin(),
       E = MBB->getFirstTerminator(); I != E; ++I) {
    if (I->isDebugValue())
      continue;

    if (++InstrCount > BlockInstrLimit && !Stress) {
      DEBUG(dbgs() << "BB#" << MBB->getNumber() << " has more than "
                   << BlockInstrLimit << " instructions.\n");
      return false;
    }

    // There shouldn't normally be any phis in a single-predecessor block.
    if (I->isPHI()) {
      DEBUG(dbgs() << "Can't hoist: " << *I);
      return false;
    }

    // Don't speculate loads. Note that it may be possible and desirable to
    // speculate GOT or constant pool loads that are guaranteed not to trap,
    // but we don't support that for now.
    if (I->mayLoad()) {
      DEBUG(dbgs() << "Won't speculate load: " << *I);
      return false;
    }

    // We never speculate stores, so an AA pointer isn't necessary.
    bool DontMoveAcrossStore = true;
    if (!I->isSafeToMove(nullptr, DontMoveAcrossStore)) {
      DEBUG(dbgs() << "Can't speculate: " << *I);
      return false;
    }

    // Check for any dependencies on Head instructions.
    for (MIOperands MO(I); MO.isValid(); ++MO) {
      if (MO->isRegMask()) {
        DEBUG(dbgs() << "Won't speculate regmask: " << *I);
        return false;
      }
      if (!MO->isReg())
        continue;
      unsigned Reg = MO->getReg();

      // Remember clobbered regunits.
      if (MO->isDef() && TargetRegisterInfo::isPhysicalRegister(Reg))
        for (MCRegUnitIterator Units(Reg, TRI); Units.isValid(); ++Units)
          ClobberedRegUnits.set(*Units);

      if (!MO->readsReg() || !TargetRegisterInfo::isVirtualRegister(Reg))
        continue;
      MachineInstr *DefMI = MRI->getVRegDef(Reg);
      if (!DefMI || DefMI->getParent() != Head)
        continue;
      if (InsertAfter.insert(DefMI).second)
        DEBUG(dbgs() << "BB#" << MBB->getNumber() << " depends on " << *DefMI);
      if (DefMI->isTerminator()) {
        DEBUG(dbgs() << "Can't insert instructions below terminator.\n");
        return false;
      }
    }
  }
  return true;
}