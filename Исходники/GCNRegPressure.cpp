static LaneBitmask getUsedRegMask(const MachineOperand &MO,
                                  const MachineRegisterInfo &MRI,
                                  const LiveIntervals &LIS) {
  assert(MO.isUse() && MO.isReg() &&
         TargetRegisterInfo::isVirtualRegister(MO.getReg()));

  if (auto SubReg = MO.getSubReg())
    return MRI.getTargetRegisterInfo()->getSubRegIndexLaneMask(SubReg);

  auto MaxMask = MRI.getMaxLaneMaskForVReg(MO.getReg());
  if (MaxMask == LaneBitmask::getLane(0)) // cannot have subregs
    return MaxMask;

  // For a tentative schedule LIS isn't updated yet but livemask should remain
  // the same on any schedule. Subreg defs can be reordered but they all must
  // dominate uses anyway.
  auto SI = LIS.getInstructionIndex(*MO.getParent()).getBaseIndex();
  return getLiveLaneMask(MO.getReg(), SI, LIS, MRI);
}