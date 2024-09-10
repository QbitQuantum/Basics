/// Calculate the MaxCallFrameSize and AdjustsStack
/// variables for the function's frame information and eliminate call frame
/// pseudo instructions.
void PEI::calculateCallFrameInfo(MachineFunction &MF) {
  const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
  const TargetFrameLowering *TFI = MF.getSubtarget().getFrameLowering();
  MachineFrameInfo &MFI = MF.getFrameInfo();

  unsigned MaxCallFrameSize = 0;
  bool AdjustsStack = MFI.adjustsStack();

  // Get the function call frame set-up and tear-down instruction opcode
  unsigned FrameSetupOpcode = TII.getCallFrameSetupOpcode();
  unsigned FrameDestroyOpcode = TII.getCallFrameDestroyOpcode();

  // Early exit for targets which have no call frame setup/destroy pseudo
  // instructions.
  if (FrameSetupOpcode == ~0u && FrameDestroyOpcode == ~0u)
    return;

  std::vector<MachineBasicBlock::iterator> FrameSDOps;
  for (MachineFunction::iterator BB = MF.begin(), E = MF.end(); BB != E; ++BB)
    for (MachineBasicBlock::iterator I = BB->begin(); I != BB->end(); ++I)
      if (TII.isFrameInstr(*I)) {
        unsigned Size = TII.getFrameSize(*I);
        if (Size > MaxCallFrameSize) MaxCallFrameSize = Size;
        AdjustsStack = true;
        FrameSDOps.push_back(I);
      } else if (I->isInlineAsm()) {
        // Some inline asm's need a stack frame, as indicated by operand 1.
        unsigned ExtraInfo = I->getOperand(InlineAsm::MIOp_ExtraInfo).getImm();
        if (ExtraInfo & InlineAsm::Extra_IsAlignStack)
          AdjustsStack = true;
      }

  assert(!MFI.isMaxCallFrameSizeComputed() ||
         (MFI.getMaxCallFrameSize() == MaxCallFrameSize &&
          MFI.adjustsStack() == AdjustsStack));
  MFI.setAdjustsStack(AdjustsStack);
  MFI.setMaxCallFrameSize(MaxCallFrameSize);

  for (std::vector<MachineBasicBlock::iterator>::iterator
         i = FrameSDOps.begin(), e = FrameSDOps.end(); i != e; ++i) {
    MachineBasicBlock::iterator I = *i;

    // If call frames are not being included as part of the stack frame, and
    // the target doesn't indicate otherwise, remove the call frame pseudos
    // here. The sub/add sp instruction pairs are still inserted, but we don't
    // need to track the SP adjustment for frame index elimination.
    if (TFI->canSimplifyCallFramePseudos(MF))
      TFI->eliminateCallFramePseudoInstr(MF, *I->getParent(), I);
  }
}