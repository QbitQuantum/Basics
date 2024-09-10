/// foldMemoryOperand - Attempt to fold a load or store of the specified stack
/// slot into the specified machine instruction for the specified operand(s).
/// If this is possible, a new instruction is returned with the specified
/// operand folded, otherwise NULL is returned. The client is responsible for
/// removing the old instruction and adding the new one in the instruction
/// stream.
MachineInstr*
TargetInstrInfo::foldMemoryOperand(MachineBasicBlock::iterator MI,
                                   const SmallVectorImpl<unsigned> &Ops,
                                   int FI) const {
  unsigned Flags = 0;
  for (unsigned i = 0, e = Ops.size(); i != e; ++i)
    if (MI->getOperand(Ops[i]).isDef())
      Flags |= MachineMemOperand::MOStore;
    else
      Flags |= MachineMemOperand::MOLoad;

  MachineBasicBlock *MBB = MI->getParent();
  assert(MBB && "foldMemoryOperand needs an inserted instruction");
  MachineFunction &MF = *MBB->getParent();

  MachineInstr *NewMI = nullptr;

  if (MI->getOpcode() == TargetOpcode::STACKMAP ||
      MI->getOpcode() == TargetOpcode::PATCHPOINT) {
    // Fold stackmap/patchpoint.
    NewMI = foldPatchpoint(MF, MI, Ops, FI, *this);
  } else {
    // Ask the target to do the actual folding.
    NewMI =foldMemoryOperandImpl(MF, MI, Ops, FI);
  }
 
  if (NewMI) {
    NewMI->setMemRefs(MI->memoperands_begin(), MI->memoperands_end());
    // Add a memory operand, foldMemoryOperandImpl doesn't do that.
    assert((!(Flags & MachineMemOperand::MOStore) ||
            NewMI->mayStore()) &&
           "Folded a def to a non-store!");
    assert((!(Flags & MachineMemOperand::MOLoad) ||
            NewMI->mayLoad()) &&
           "Folded a use to a non-load!");
    const MachineFrameInfo &MFI = *MF.getFrameInfo();
    assert(MFI.getObjectOffset(FI) != -1);
    MachineMemOperand *MMO =
      MF.getMachineMemOperand(MachinePointerInfo::getFixedStack(FI),
                              Flags, MFI.getObjectSize(FI),
                              MFI.getObjectAlignment(FI));
    NewMI->addMemOperand(MF, MMO);

    // FIXME: change foldMemoryOperandImpl semantics to also insert NewMI.
    return MBB->insert(MI, NewMI);
  }

  // Straight COPY may fold as load/store.
  if (!MI->isCopy() || Ops.size() != 1)
    return nullptr;

  const TargetRegisterClass *RC = canFoldCopy(MI, Ops[0]);
  if (!RC)
    return nullptr;

  const MachineOperand &MO = MI->getOperand(1-Ops[0]);
  MachineBasicBlock::iterator Pos = MI;
  const TargetRegisterInfo *TRI = MF.getTarget().getRegisterInfo();

  if (Flags == MachineMemOperand::MOStore)
    storeRegToStackSlot(*MBB, Pos, MO.getReg(), MO.isKill(), FI, RC, TRI);
  else
    loadRegFromStackSlot(*MBB, Pos, MO.getReg(), FI, RC, TRI);
  return --Pos;
}