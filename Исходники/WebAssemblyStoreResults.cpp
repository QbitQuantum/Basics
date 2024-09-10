// Replace uses of FromReg with ToReg if they are dominated by MI.
static bool ReplaceDominatedUses(MachineBasicBlock &MBB, MachineInstr &MI,
                                 unsigned FromReg, unsigned ToReg,
                                 const MachineRegisterInfo &MRI,
                                 MachineDominatorTree &MDT,
                                 LiveIntervals &LIS) {
  bool Changed = false;

  LiveInterval *FromLI = &LIS.getInterval(FromReg);
  LiveInterval *ToLI = &LIS.getInterval(ToReg);

  SlotIndex FromIdx = LIS.getInstructionIndex(MI).getRegSlot();
  VNInfo *FromVNI = FromLI->getVNInfoAt(FromIdx);

  SmallVector<SlotIndex, 4> Indices;

  for (auto I = MRI.use_nodbg_begin(FromReg), E = MRI.use_nodbg_end();
       I != E;) {
    MachineOperand &O = *I++;
    MachineInstr *Where = O.getParent();

    // Check that MI dominates the instruction in the normal way.
    if (&MI == Where || !MDT.dominates(&MI, Where))
      continue;

    // If this use gets a different value, skip it.
    SlotIndex WhereIdx = LIS.getInstructionIndex(*Where);
    VNInfo *WhereVNI = FromLI->getVNInfoAt(WhereIdx);
    if (WhereVNI && WhereVNI != FromVNI)
      continue;

    // Make sure ToReg isn't clobbered before it gets there.
    VNInfo *ToVNI = ToLI->getVNInfoAt(WhereIdx);
    if (ToVNI && ToVNI != FromVNI)
      continue;

    Changed = true;
    LLVM_DEBUG(dbgs() << "Setting operand " << O << " in " << *Where << " from "
                      << MI << "\n");
    O.setReg(ToReg);

    // If the store's def was previously dead, it is no longer.
    if (!O.isUndef()) {
      MI.getOperand(0).setIsDead(false);

      Indices.push_back(WhereIdx.getRegSlot());
    }
  }

  if (Changed) {
    // Extend ToReg's liveness.
    LIS.extendToIndices(*ToLI, Indices);

    // Shrink FromReg's liveness.
    LIS.shrinkToUses(FromLI);

    // If we replaced all dominated uses, FromReg is now killed at MI.
    if (!FromLI->liveAt(FromIdx.getDeadSlot()))
      MI.addRegisterKilled(FromReg, MBB.getParent()
                                        ->getSubtarget<WebAssemblySubtarget>()
                                        .getRegisterInfo());
  }

  return Changed;
}