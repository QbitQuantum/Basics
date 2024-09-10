bool AArch64LoadStoreOpt::tryToMergeLdStInst(
    MachineBasicBlock::iterator &MBBI) {
  MachineInstr *MI = MBBI;
  MachineBasicBlock::iterator E = MI->getParent()->end();
  // If this is a volatile load/store, don't mess with it.
  if (MI->hasOrderedMemoryRef())
    return false;

  // Make sure this is a reg+imm (as opposed to an address reloc).
  if (!getLdStOffsetOp(MI).isImm())
    return false;

  // Check if this load/store has a hint to avoid pair formation.
  // MachineMemOperands hints are set by the AArch64StorePairSuppress pass.
  if (TII->isLdStPairSuppressed(MI))
    return false;

  // Look ahead up to ScanLimit instructions for a pairable instruction.
  LdStPairFlags Flags;
  MachineBasicBlock::iterator Paired = findMatchingInsn(MBBI, Flags, ScanLimit);
  if (Paired != E) {
    if (isSmallTypeLdMerge(MI)) {
      ++NumSmallTypeMerged;
    } else {
      ++NumPairCreated;
      if (isUnscaledLdSt(MI))
        ++NumUnscaledPairCreated;
    }

    // Merge the loads into a pair. Keeping the iterator straight is a
    // pain, so we let the merge routine tell us what the next instruction
    // is after it's done mucking about.
    MBBI = mergePairedInsns(MBBI, Paired, Flags);
    return true;
  }
  return false;
}