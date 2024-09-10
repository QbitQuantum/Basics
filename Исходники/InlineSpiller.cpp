/// spillAroundUses - insert spill code around each use of Reg.
void InlineSpiller::spillAroundUses(unsigned Reg) {
  DEBUG(dbgs() << "spillAroundUses " << PrintReg(Reg) << '\n');
  LiveInterval &OldLI = LIS.getInterval(Reg);

  // Iterate over instructions using Reg.
  for (MachineRegisterInfo::reg_bundle_iterator
       RegI = MRI.reg_bundle_begin(Reg), E = MRI.reg_bundle_end();
       RegI != E; ) {
    MachineInstr *MI = &*(RegI++);

    // Debug values are not allowed to affect codegen.
    if (MI->isDebugValue()) {
      // Modify DBG_VALUE now that the value is in a spill slot.
      bool IsIndirect = MI->isIndirectDebugValue();
      uint64_t Offset = IsIndirect ? MI->getOperand(1).getImm() : 0;
      const MDNode *MDPtr = MI->getOperand(2).getMetadata();
      DebugLoc DL = MI->getDebugLoc();
      DEBUG(dbgs() << "Modifying debug info due to spill:" << "\t" << *MI);
      MachineBasicBlock *MBB = MI->getParent();
      BuildMI(*MBB, MBB->erase(MI), DL, TII.get(TargetOpcode::DBG_VALUE))
          .addFrameIndex(StackSlot).addImm(Offset).addMetadata(MDPtr);
      continue;
    }

    // Ignore copies to/from snippets. We'll delete them.
    if (SnippetCopies.count(MI))
      continue;

    // Stack slot accesses may coalesce away.
    if (coalesceStackAccess(MI, Reg))
      continue;

    // Analyze instruction.
    SmallVector<std::pair<MachineInstr*, unsigned>, 8> Ops;
    MIBundleOperands::VirtRegInfo RI =
      MIBundleOperands(MI).analyzeVirtReg(Reg, &Ops);

    // Find the slot index where this instruction reads and writes OldLI.
    // This is usually the def slot, except for tied early clobbers.
    SlotIndex Idx = LIS.getInstructionIndex(MI).getRegSlot();
    if (VNInfo *VNI = OldLI.getVNInfoAt(Idx.getRegSlot(true)))
      if (SlotIndex::isSameInstr(Idx, VNI->def))
        Idx = VNI->def;

    // Check for a sibling copy.
    unsigned SibReg = isFullCopyOf(MI, Reg);
    if (SibReg && isSibling(SibReg)) {
      // This may actually be a copy between snippets.
      if (isRegToSpill(SibReg)) {
        DEBUG(dbgs() << "Found new snippet copy: " << *MI);
        SnippetCopies.insert(MI);
        continue;
      }
      if (RI.Writes) {
        // Hoist the spill of a sib-reg copy.
        if (hoistSpill(OldLI, MI)) {
          // This COPY is now dead, the value is already in the stack slot.
          MI->getOperand(0).setIsDead();
          DeadDefs.push_back(MI);
          continue;
        }
      } else {
        // This is a reload for a sib-reg copy. Drop spills downstream.
        LiveInterval &SibLI = LIS.getInterval(SibReg);
        eliminateRedundantSpills(SibLI, SibLI.getVNInfoAt(Idx));
        // The COPY will fold to a reload below.
      }
    }

    // Attempt to fold memory ops.
    if (foldMemoryOperand(Ops))
      continue;

    // Create a new virtual register for spill/fill.
    // FIXME: Infer regclass from instruction alone.
    unsigned NewVReg = Edit->createFrom(Reg);

    if (RI.Reads)
      insertReload(NewVReg, Idx, MI);

    // Rewrite instruction operands.
    bool hasLiveDef = false;
    for (unsigned i = 0, e = Ops.size(); i != e; ++i) {
      MachineOperand &MO = Ops[i].first->getOperand(Ops[i].second);
      MO.setReg(NewVReg);
      if (MO.isUse()) {
        if (!Ops[i].first->isRegTiedToDefOperand(Ops[i].second))
          MO.setIsKill();
      } else {
        if (!MO.isDead())
          hasLiveDef = true;
      }
    }
    DEBUG(dbgs() << "\trewrite: " << Idx << '\t' << *MI << '\n');

    // FIXME: Use a second vreg if instruction has no tied ops.
    if (RI.Writes)
      if (hasLiveDef)
        insertSpill(NewVReg, true, MI);
  }
}