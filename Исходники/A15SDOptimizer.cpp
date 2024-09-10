// MI is known to be dead. Figure out what instructions
// are also made dead by this and mark them for removal.
void A15SDOptimizer::eraseInstrWithNoUses(MachineInstr *MI) {
  SmallVector<MachineInstr *, 8> Front;
  DeadInstr.insert(MI);

  DEBUG(dbgs() << "Deleting base instruction " << *MI << "\n");
  Front.push_back(MI);

  while (Front.size() != 0) {
    MI = Front.back();
    Front.pop_back();

    // MI is already known to be dead. We need to see
    // if other instructions can also be removed.
    for (unsigned int i = 0; i < MI->getNumOperands(); ++i) {
      MachineOperand &MO = MI->getOperand(i);
      if ((!MO.isReg()) || (!MO.isUse()))
        continue;
      unsigned Reg = MO.getReg();
      if (!TRI->isVirtualRegister(Reg))
        continue;
      MachineOperand *Op = MI->findRegisterDefOperand(Reg);

      if (!Op)
        continue;

      MachineInstr *Def = Op->getParent();

      // We don't need to do anything if we have already marked
      // this instruction as being dead.
      if (DeadInstr.find(Def) != DeadInstr.end())
        continue;

      // Check if all the uses of this instruction are marked as
      // dead. If so, we can also mark this instruction as being
      // dead.
      bool IsDead = true;
      for (unsigned int j = 0; j < Def->getNumOperands(); ++j) {
        MachineOperand &MODef = Def->getOperand(j);
        if ((!MODef.isReg()) || (!MODef.isDef()))
          continue;
        unsigned DefReg = MODef.getReg();
        if (!TRI->isVirtualRegister(DefReg)) {
          IsDead = false;
          break;
        }
        for (MachineRegisterInfo::use_instr_iterator
             II = MRI->use_instr_begin(Reg), EE = MRI->use_instr_end();
             II != EE; ++II) {
          // We don't care about self references.
          if (&*II == Def)
            continue;
          if (DeadInstr.find(&*II) == DeadInstr.end()) {
            IsDead = false;
            break;
          }
        }
      }

      if (!IsDead) continue;

      DEBUG(dbgs() << "Deleting instruction " << *Def << "\n");
      DeadInstr.insert(Def);
    }
  }
}