/// finalizeBundle - Finalize a machine instruction bundle which includes
/// a sequence of instructions starting from FirstMI to LastMI (exclusive).
/// This routine adds a BUNDLE instruction to represent the bundle, it adds
/// IsInternalRead markers to MachineOperands which are defined inside the
/// bundle, and it copies externally visible defs and uses to the BUNDLE
/// instruction.
void llvm::finalizeBundle(MachineBasicBlock &MBB,
                          MachineBasicBlock::instr_iterator FirstMI,
                          MachineBasicBlock::instr_iterator LastMI) {
  assert(FirstMI != LastMI && "Empty bundle?");
  MIBundleBuilder Bundle(MBB, FirstMI, LastMI);

  const TargetMachine &TM = MBB.getParent()->getTarget();
  const TargetInstrInfo *TII = TM.getInstrInfo();
  const TargetRegisterInfo *TRI = TM.getRegisterInfo();

  MachineInstrBuilder MIB = BuildMI(*MBB.getParent(), FirstMI->getDebugLoc(),
                                    TII->get(TargetOpcode::BUNDLE));
  Bundle.prepend(MIB);

  SmallVector<unsigned, 32> LocalDefs;
  SmallSet<unsigned, 32> LocalDefSet;
  SmallSet<unsigned, 8> DeadDefSet;
  SmallSet<unsigned, 16> KilledDefSet;
  SmallVector<unsigned, 8> ExternUses;
  SmallSet<unsigned, 8> ExternUseSet;
  SmallSet<unsigned, 8> KilledUseSet;
  SmallSet<unsigned, 8> UndefUseSet;
  SmallVector<MachineOperand*, 4> Defs;
  for (; FirstMI != LastMI; ++FirstMI) {
    for (unsigned i = 0, e = FirstMI->getNumOperands(); i != e; ++i) {
      MachineOperand &MO = FirstMI->getOperand(i);
      if (!MO.isReg())
        continue;
      if (MO.isDef()) {
        Defs.push_back(&MO);
        continue;
      }

      unsigned Reg = MO.getReg();
      if (!Reg)
        continue;
      assert(TargetRegisterInfo::isPhysicalRegister(Reg));
      if (LocalDefSet.count(Reg)) {
        MO.setIsInternalRead();
        if (MO.isKill())
          // Internal def is now killed.
          KilledDefSet.insert(Reg);
      } else {
        if (ExternUseSet.insert(Reg)) {
          ExternUses.push_back(Reg);
          if (MO.isUndef())
            UndefUseSet.insert(Reg);
        }
        if (MO.isKill())
          // External def is now killed.
          KilledUseSet.insert(Reg);
      }
    }

    for (unsigned i = 0, e = Defs.size(); i != e; ++i) {
      MachineOperand &MO = *Defs[i];
      unsigned Reg = MO.getReg();
      if (!Reg)
        continue;

      if (LocalDefSet.insert(Reg)) {
        LocalDefs.push_back(Reg);
        if (MO.isDead()) {
          DeadDefSet.insert(Reg);
        }
      } else {
        // Re-defined inside the bundle, it's no longer killed.
        KilledDefSet.erase(Reg);
        if (!MO.isDead())
          // Previously defined but dead.
          DeadDefSet.erase(Reg);
      }

      if (!MO.isDead()) {
        for (MCSubRegIterator SubRegs(Reg, TRI); SubRegs.isValid(); ++SubRegs) {
          unsigned SubReg = *SubRegs;
          if (LocalDefSet.insert(SubReg))
            LocalDefs.push_back(SubReg);
        }
      }
    }

    Defs.clear();
  }

  SmallSet<unsigned, 32> Added;
  for (unsigned i = 0, e = LocalDefs.size(); i != e; ++i) {
    unsigned Reg = LocalDefs[i];
    if (Added.insert(Reg)) {
      // If it's not live beyond end of the bundle, mark it dead.
      bool isDead = DeadDefSet.count(Reg) || KilledDefSet.count(Reg);
      MIB.addReg(Reg, getDefRegState(true) | getDeadRegState(isDead) |
                 getImplRegState(true));
    }
  }

  for (unsigned i = 0, e = ExternUses.size(); i != e; ++i) {
    unsigned Reg = ExternUses[i];
    bool isKill = KilledUseSet.count(Reg);
    bool isUndef = UndefUseSet.count(Reg);
    MIB.addReg(Reg, getKillRegState(isKill) | getUndefRegState(isUndef) |
               getImplRegState(true));
  }
}