/// Returns true if the given machine operand \p MO only reads undefined lanes.
/// The function only works for use operands with a subregister set.
bool VirtRegRewriter::readsUndefSubreg(const MachineOperand &MO) const {
  // Shortcut if the operand is already marked undef.
  if (MO.isUndef())
    return true;

  unsigned Reg = MO.getReg();
  const LiveInterval &LI = LIS->getInterval(Reg);
  const MachineInstr &MI = *MO.getParent();
  SlotIndex BaseIndex = LIS->getInstructionIndex(MI);
  // This code is only meant to handle reading undefined subregisters which
  // we couldn't properly detect before.
  assert(LI.liveAt(BaseIndex) &&
         "Reads of completely dead register should be marked undef already");
  unsigned SubRegIdx = MO.getSubReg();
  LaneBitmask UseMask = TRI->getSubRegIndexLaneMask(SubRegIdx);
  // See if any of the relevant subregister liveranges is defined at this point.
  for (const LiveInterval::SubRange &SR : LI.subranges()) {
    if ((SR.LaneMask & UseMask) != 0 && SR.liveAt(BaseIndex))
      return false;
  }
  return true;
}