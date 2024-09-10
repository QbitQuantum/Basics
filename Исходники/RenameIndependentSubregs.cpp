bool RenameIndependentSubregs::findComponents(IntEqClasses &Classes,
    SmallVectorImpl<RenameIndependentSubregs::SubRangeInfo> &SubRangeInfos,
    LiveInterval &LI) const {
  // First step: Create connected components for the VNInfos inside the
  // subranges and count the global number of such components.
  unsigned NumComponents = 0;
  for (LiveInterval::SubRange &SR : LI.subranges()) {
    SubRangeInfos.push_back(SubRangeInfo(*LIS, SR, NumComponents));
    ConnectedVNInfoEqClasses &ConEQ = SubRangeInfos.back().ConEQ;

    unsigned NumSubComponents = ConEQ.Classify(SR);
    NumComponents += NumSubComponents;
  }
  // Shortcut: With only 1 subrange, the normal separate component tests are
  // enough and we do not need to perform the union-find on the subregister
  // segments.
  if (SubRangeInfos.size() < 2)
    return false;

  // Next step: Build union-find structure over all subranges and merge classes
  // across subranges when they are affected by the same MachineOperand.
  const TargetRegisterInfo &TRI = *MRI->getTargetRegisterInfo();
  Classes.grow(NumComponents);
  unsigned Reg = LI.reg;
  for (const MachineOperand &MO : MRI->reg_nodbg_operands(Reg)) {
    if (!MO.isDef() && !MO.readsReg())
      continue;
    unsigned SubRegIdx = MO.getSubReg();
    LaneBitmask LaneMask = TRI.getSubRegIndexLaneMask(SubRegIdx);
    unsigned MergedID = ~0u;
    for (RenameIndependentSubregs::SubRangeInfo &SRInfo : SubRangeInfos) {
      const LiveInterval::SubRange &SR = *SRInfo.SR;
      if ((SR.LaneMask & LaneMask) == 0)
        continue;
      SlotIndex Pos = LIS->getInstructionIndex(*MO.getParent());
      Pos = MO.isDef() ? Pos.getRegSlot(MO.isEarlyClobber())
                       : Pos.getBaseIndex();
      const VNInfo *VNI = SR.getVNInfoAt(Pos);
      if (VNI == nullptr)
        continue;

      // Map to local representant ID.
      unsigned LocalID = SRInfo.ConEQ.getEqClass(VNI);
      // Global ID
      unsigned ID = LocalID + SRInfo.Index;
      // Merge other sets
      MergedID = MergedID == ~0u ? ID : Classes.join(MergedID, ID);
    }
  }

  // Early exit if we ended up with a single equivalence class.
  Classes.compress();
  unsigned NumClasses = Classes.getNumClasses();
  return NumClasses > 1;
}