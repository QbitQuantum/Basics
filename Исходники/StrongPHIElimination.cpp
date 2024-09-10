bool StrongPHIElimination::runOnMachineFunction(MachineFunction &MF) {
  MRI = &MF.getRegInfo();
  TII = MF.getTarget().getInstrInfo();
  DT = &getAnalysis<MachineDominatorTree>();
  LI = &getAnalysis<LiveIntervals>();

  for (MachineFunction::iterator I = MF.begin(), E = MF.end();
       I != E; ++I) {
    for (MachineBasicBlock::iterator BBI = I->begin(), BBE = I->end();
         BBI != BBE && BBI->isPHI(); ++BBI) {
      unsigned DestReg = BBI->getOperand(0).getReg();
      addReg(DestReg);
      PHISrcDefs[I].push_back(BBI);

      for (unsigned i = 1; i < BBI->getNumOperands(); i += 2) {
        MachineOperand &SrcMO = BBI->getOperand(i);
        unsigned SrcReg = SrcMO.getReg();
        addReg(SrcReg);
        unionRegs(DestReg, SrcReg);

        MachineInstr *DefMI = MRI->getVRegDef(SrcReg);
        if (DefMI)
          PHISrcDefs[DefMI->getParent()].push_back(DefMI);
      }
    }
  }

  // Perform a depth-first traversal of the dominator tree, splitting
  // interferences amongst PHI-congruence classes.
  DenseMap<unsigned, unsigned> CurrentDominatingParent;
  DenseMap<unsigned, unsigned> ImmediateDominatingParent;
  for (df_iterator<MachineDomTreeNode*> DI = df_begin(DT->getRootNode()),
       DE = df_end(DT->getRootNode()); DI != DE; ++DI) {
    SplitInterferencesForBasicBlock(*DI->getBlock(),
                                    CurrentDominatingParent,
                                    ImmediateDominatingParent);
  }

  // Insert copies for all PHI source and destination registers.
  for (MachineFunction::iterator I = MF.begin(), E = MF.end();
       I != E; ++I) {
    for (MachineBasicBlock::iterator BBI = I->begin(), BBE = I->end();
         BBI != BBE && BBI->isPHI(); ++BBI) {
      InsertCopiesForPHI(BBI, I);
    }
  }

  // FIXME: Preserve the equivalence classes during copy insertion and use
  // the preversed equivalence classes instead of recomputing them.
  RegNodeMap.clear();
  for (MachineFunction::iterator I = MF.begin(), E = MF.end();
       I != E; ++I) {
    for (MachineBasicBlock::iterator BBI = I->begin(), BBE = I->end();
         BBI != BBE && BBI->isPHI(); ++BBI) {
      unsigned DestReg = BBI->getOperand(0).getReg();
      addReg(DestReg);

      for (unsigned i = 1; i < BBI->getNumOperands(); i += 2) {
        unsigned SrcReg = BBI->getOperand(i).getReg();
        addReg(SrcReg);
        unionRegs(DestReg, SrcReg);
      }
    }
  }

  DenseMap<unsigned, unsigned> RegRenamingMap;
  bool Changed = false;
  for (MachineFunction::iterator I = MF.begin(), E = MF.end();
       I != E; ++I) {
    MachineBasicBlock::iterator BBI = I->begin(), BBE = I->end();
    while (BBI != BBE && BBI->isPHI()) {
      MachineInstr *PHI = BBI;

      assert(PHI->getNumOperands() > 0);

      unsigned SrcReg = PHI->getOperand(1).getReg();
      unsigned SrcColor = getRegColor(SrcReg);
      unsigned NewReg = RegRenamingMap[SrcColor];
      if (!NewReg) {
        NewReg = SrcReg;
        RegRenamingMap[SrcColor] = SrcReg;
      }
      MergeLIsAndRename(SrcReg, NewReg);

      unsigned DestReg = PHI->getOperand(0).getReg();
      if (!InsertedDestCopies.count(DestReg))
        MergeLIsAndRename(DestReg, NewReg);

      for (unsigned i = 3; i < PHI->getNumOperands(); i += 2) {
        unsigned SrcReg = PHI->getOperand(i).getReg();
        MergeLIsAndRename(SrcReg, NewReg);
      }

      ++BBI;
      LI->RemoveMachineInstrFromMaps(PHI);
      PHI->eraseFromParent();
      Changed = true;
    }
  }

  // Due to the insertion of copies to split live ranges, the live intervals are
  // guaranteed to not overlap, except in one case: an original PHI source and a
  // PHI destination copy. In this case, they have the same value and thus don't
  // truly intersect, so we merge them into the value live at that point.
  // FIXME: Is there some better way we can handle this?
  for (DestCopyMap::iterator I = InsertedDestCopies.begin(),
       E = InsertedDestCopies.end(); I != E; ++I) {
    unsigned DestReg = I->first;
    unsigned DestColor = getRegColor(DestReg);
    unsigned NewReg = RegRenamingMap[DestColor];

    LiveInterval &DestLI = LI->getInterval(DestReg);
    LiveInterval &NewLI = LI->getInterval(NewReg);

    assert(DestLI.ranges.size() == 1
           && "PHI destination copy's live interval should be a single live "
               "range from the beginning of the BB to the copy instruction.");
    LiveRange *DestLR = DestLI.begin();
    VNInfo *NewVNI = NewLI.getVNInfoAt(DestLR->start);
    if (!NewVNI) {
      NewVNI = NewLI.createValueCopy(DestLR->valno, LI->getVNInfoAllocator());
      MachineInstr *CopyInstr = I->second;
      CopyInstr->getOperand(1).setIsKill(true);
    }

    LiveRange NewLR(DestLR->start, DestLR->end, NewVNI);
    NewLI.addRange(NewLR);

    LI->removeInterval(DestReg);
    MRI->replaceRegWith(DestReg, NewReg);
  }

  // Adjust the live intervals of all PHI source registers to handle the case
  // where the PHIs in successor blocks were the only later uses of the source
  // register.
  for (SrcCopySet::iterator I = InsertedSrcCopySet.begin(),
       E = InsertedSrcCopySet.end(); I != E; ++I) {
    MachineBasicBlock *MBB = I->first;
    unsigned SrcReg = I->second;
    if (unsigned RenamedRegister = RegRenamingMap[getRegColor(SrcReg)])
      SrcReg = RenamedRegister;

    LiveInterval &SrcLI = LI->getInterval(SrcReg);

    bool isLiveOut = false;
    for (MachineBasicBlock::succ_iterator SI = MBB->succ_begin(),
         SE = MBB->succ_end(); SI != SE; ++SI) {
      if (SrcLI.liveAt(LI->getMBBStartIdx(*SI))) {
        isLiveOut = true;
        break;
      }
    }

    if (isLiveOut)
      continue;

    MachineOperand *LastUse = findLastUse(MBB, SrcReg);
    assert(LastUse);
    SlotIndex LastUseIndex = LI->getInstructionIndex(LastUse->getParent());
    SrcLI.removeRange(LastUseIndex.getRegSlot(), LI->getMBBEndIdx(MBB));
    LastUse->setIsKill(true);
  }

  Allocator.Reset();
  RegNodeMap.clear();
  PHISrcDefs.clear();
  InsertedSrcCopySet.clear();
  InsertedSrcCopyMap.clear();
  InsertedDestCopies.clear();

  return Changed;
}