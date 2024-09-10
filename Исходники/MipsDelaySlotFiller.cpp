/// runOnMachineBasicBlock - Fill in delay slots for the given basic block.
/// We assume there is only one delay slot per delayed instruction.
bool Filler::runOnMachineBasicBlock(MachineBasicBlock &MBB) {
  bool Changed = false;
  const MipsSubtarget &STI = MBB.getParent()->getSubtarget<MipsSubtarget>();
  bool InMicroMipsMode = STI.inMicroMipsMode();
  const MipsInstrInfo *TII = STI.getInstrInfo();

  for (Iter I = MBB.begin(); I != MBB.end(); ++I) {
    if (!hasUnoccupiedSlot(&*I))
      continue;

    ++FilledSlots;
    Changed = true;

    // Delay slot filling is disabled at -O0.
    if (!DisableDelaySlotFiller && (TM.getOptLevel() != CodeGenOpt::None)) {
      bool Filled = false;

      if (searchBackward(MBB, I)) {
        Filled = true;
      } else if (I->isTerminator()) {
        if (searchSuccBBs(MBB, I)) {
          Filled = true;
        }
      } else if (searchForward(MBB, I)) {
        Filled = true;
      }

      if (Filled) {
        // Get instruction with delay slot.
        MachineBasicBlock::instr_iterator DSI(I);

        if (InMicroMipsMode && TII->GetInstSizeInBytes(std::next(DSI)) == 2 &&
            DSI->isCall()) {
          // If instruction in delay slot is 16b change opcode to
          // corresponding instruction with short delay slot.
          DSI->setDesc(TII->get(getEquivalentCallShort(DSI->getOpcode())));
        }

        continue;
      }
    }

    // If instruction is BEQ or BNE with one ZERO register, then instead of
    // adding NOP replace this instruction with the corresponding compact
    // branch instruction, i.e. BEQZC or BNEZC.
    unsigned Opcode = I->getOpcode();
    if (InMicroMipsMode &&
        (Opcode == Mips::BEQ || Opcode == Mips::BNE) &&
        ((unsigned) I->getOperand(1).getReg()) == Mips::ZERO) {

      I = replaceWithCompactBranch(MBB, I, I->getDebugLoc());

    } else {
      // Bundle the NOP to the instruction with the delay slot.
      BuildMI(MBB, std::next(I), I->getDebugLoc(), TII->get(Mips::NOP));
      MIBundleBuilder(MBB, I, std::next(I, 2));
    }
  }

  return Changed;
}