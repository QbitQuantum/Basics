bool Thumb1FrameLowering::emitPopSpecialFixUp(MachineBasicBlock &MBB,
                                              bool DoIt) const {
  MachineFunction &MF = *MBB.getParent();
  ARMFunctionInfo *AFI = MF.getInfo<ARMFunctionInfo>();
  unsigned ArgRegsSaveSize = AFI->getArgRegsSaveSize();
  const TargetInstrInfo &TII = *STI.getInstrInfo();
  const ThumbRegisterInfo *RegInfo =
      static_cast<const ThumbRegisterInfo *>(STI.getRegisterInfo());

  // If MBBI is a return instruction, or is a tPOP followed by a return
  // instruction in the successor BB, we may be able to directly restore
  // LR in the PC.
  // This is only possible with v5T ops (v4T can't change the Thumb bit via
  // a POP PC instruction), and only if we do not need to emit any SP update.
  // Otherwise, we need a temporary register to pop the value
  // and copy that value into LR.
  auto MBBI = MBB.getFirstTerminator();
  bool CanRestoreDirectly = STI.hasV5TOps() && !ArgRegsSaveSize;
  if (CanRestoreDirectly) {
    if (MBBI != MBB.end())
      CanRestoreDirectly = (MBBI->getOpcode() == ARM::tBX_RET ||
                            MBBI->getOpcode() == ARM::tPOP_RET);
    else {
      assert(MBB.back().getOpcode() == ARM::tPOP);
      assert(MBB.succ_size() == 1);
      if ((*MBB.succ_begin())->begin()->getOpcode() == ARM::tBX_RET)
        MBBI--; // Replace the final tPOP with a tPOP_RET.
      else
        CanRestoreDirectly = false;
    }
  }

  if (CanRestoreDirectly) {
    if (!DoIt || MBBI->getOpcode() == ARM::tPOP_RET)
      return true;
    MachineInstrBuilder MIB =
        AddDefaultPred(
            BuildMI(MBB, MBBI, MBBI->getDebugLoc(), TII.get(ARM::tPOP_RET)));
    // Copy implicit ops and popped registers, if any.
    for (auto MO: MBBI->operands())
      if (MO.isReg() && (MO.isImplicit() || MO.isDef()) &&
          MO.getReg() != ARM::LR)
        MIB.addOperand(MO);
    MIB.addReg(ARM::PC, RegState::Define);
    // Erase the old instruction (tBX_RET or tPOP).
    MBB.erase(MBBI);
    return true;
  }

  // Look for a temporary register to use.
  // First, compute the liveness information.
  LivePhysRegs UsedRegs(STI.getRegisterInfo());
  UsedRegs.addLiveOuts(&MBB, /*AddPristines*/ true);
  // The semantic of pristines changed recently and now,
  // the callee-saved registers that are touched in the function
  // are not part of the pristines set anymore.
  // Add those callee-saved now.
  const TargetRegisterInfo *TRI = STI.getRegisterInfo();
  const MCPhysReg *CSRegs = TRI->getCalleeSavedRegs(&MF);
  for (unsigned i = 0; CSRegs[i]; ++i)
    UsedRegs.addReg(CSRegs[i]);

  DebugLoc dl = DebugLoc();
  if (MBBI != MBB.end()) {
    dl = MBBI->getDebugLoc();
    auto InstUpToMBBI = MBB.end();
    while (InstUpToMBBI != MBBI)
      // The pre-decrement is on purpose here.
      // We want to have the liveness right before MBBI.
      UsedRegs.stepBackward(*--InstUpToMBBI);
  }

  // Look for a register that can be directly use in the POP.
  unsigned PopReg = 0;
  // And some temporary register, just in case.
  unsigned TemporaryReg = 0;
  BitVector PopFriendly =
      TRI->getAllocatableSet(MF, TRI->getRegClass(ARM::tGPRRegClassID));
  assert(PopFriendly.any() && "No allocatable pop-friendly register?!");
  // Rebuild the GPRs from the high registers because they are removed
  // form the GPR reg class for thumb1.
  BitVector GPRsNoLRSP =
      TRI->getAllocatableSet(MF, TRI->getRegClass(ARM::hGPRRegClassID));
  GPRsNoLRSP |= PopFriendly;
  GPRsNoLRSP.reset(ARM::LR);
  GPRsNoLRSP.reset(ARM::SP);
  GPRsNoLRSP.reset(ARM::PC);
  for (int Register = GPRsNoLRSP.find_first(); Register != -1;
       Register = GPRsNoLRSP.find_next(Register)) {
    if (!UsedRegs.contains(Register)) {
      // Remember the first pop-friendly register and exit.
      if (PopFriendly.test(Register)) {
        PopReg = Register;
        TemporaryReg = 0;
        break;
      }
      // Otherwise, remember that the register will be available to
      // save a pop-friendly register.
      TemporaryReg = Register;
    }
  }

  if (!DoIt && !PopReg && !TemporaryReg)
    return false;

  assert((PopReg || TemporaryReg) && "Cannot get LR");

  if (TemporaryReg) {
    assert(!PopReg && "Unnecessary MOV is about to be inserted");
    PopReg = PopFriendly.find_first();
    AddDefaultPred(BuildMI(MBB, MBBI, dl, TII.get(ARM::tMOVr))
                       .addReg(TemporaryReg, RegState::Define)
                       .addReg(PopReg, RegState::Kill));
  }

  if (MBBI == MBB.end()) {
    MachineInstr& Pop = MBB.back();
    assert(Pop.getOpcode() == ARM::tPOP);
    Pop.RemoveOperand(Pop.findRegisterDefOperandIdx(ARM::LR));
  }

  assert(PopReg && "Do not know how to get LR");
  AddDefaultPred(BuildMI(MBB, MBBI, dl, TII.get(ARM::tPOP)))
      .addReg(PopReg, RegState::Define);

  emitSPUpdate(MBB, MBBI, TII, dl, *RegInfo, ArgRegsSaveSize);

  if (!TemporaryReg && MBBI != MBB.end() && MBBI->getOpcode() == ARM::tBX_RET) {
    MachineInstrBuilder MIB = BuildMI(MBB, MBBI, dl, TII.get(ARM::tBX))
                                  .addReg(PopReg, RegState::Kill);
    AddDefaultPred(MIB);
    MIB.copyImplicitOps(&*MBBI);
    // erase the old tBX_RET instruction
    MBB.erase(MBBI);
    return true;
  }

  AddDefaultPred(BuildMI(MBB, MBBI, dl, TII.get(ARM::tMOVr))
                     .addReg(ARM::LR, RegState::Define)
                     .addReg(PopReg, RegState::Kill));

  if (TemporaryReg) {
    AddDefaultPred(BuildMI(MBB, MBBI, dl, TII.get(ARM::tMOVr))
                       .addReg(PopReg, RegState::Define)
                       .addReg(TemporaryReg, RegState::Kill));
  }

  return true;
}