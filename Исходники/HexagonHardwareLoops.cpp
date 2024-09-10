/// converToHardwareLoop - check if the loop is a candidate for
/// converting to a hardware loop.  If so, then perform the
/// transformation.
///
/// This function works on innermost loops first.  A loop can
/// be converted if it is a counting loop; either a register
/// value or an immediate.
///
/// The code makes several assumptions about the representation
/// of the loop in llvm.
bool HexagonHardwareLoops::convertToHardwareLoop(MachineLoop *L) {
  bool Changed = false;
  // Process nested loops first.
  for (MachineLoop::iterator I = L->begin(), E = L->end(); I != E; ++I) {
    Changed |= convertToHardwareLoop(*I);
  }
  // If a nested loop has been converted, then we can't convert this loop.
  if (Changed) {
    return Changed;
  }
  // Are we able to determine the trip count for the loop?
  CountValue *TripCount = getTripCount(L);
  if (TripCount == 0) {
    return false;
  }
  // Does the loop contain any invalid instructions?
  if (containsInvalidInstruction(L)) {
    return false;
  }
  MachineBasicBlock *Preheader = L->getLoopPreheader();
  // No preheader means there's not place for the loop instr.
  if (Preheader == 0) {
    return false;
  }
  MachineBasicBlock::iterator InsertPos = Preheader->getFirstTerminator();

  MachineBasicBlock *LastMBB = L->getExitingBlock();
  // Don't generate hw loop if the loop has more than one exit.
  if (LastMBB == 0) {
    return false;
  }
  MachineBasicBlock::iterator LastI = LastMBB->getFirstTerminator();

  // Determine the loop start.
  MachineBasicBlock *LoopStart = L->getTopBlock();
  if (L->getLoopLatch() != LastMBB) {
    // When the exit and latch are not the same, use the latch block as the
    // start.
    // The loop start address is used only after the 1st iteration, and the loop
    // latch may contains instrs. that need to be executed after the 1st iter.
    LoopStart = L->getLoopLatch();
    // Make sure the latch is a successor of the exit, otherwise it won't work.
    if (!LastMBB->isSuccessor(LoopStart)) {
      return false;
    }
  }

  // Convert the loop to a hardware loop
  DEBUG(dbgs() << "Change to hardware loop at "; L->dump());

  if (TripCount->isReg()) {
    // Create a copy of the loop count register.
    MachineFunction *MF = LastMBB->getParent();
    const TargetRegisterClass *RC =
      MF->getRegInfo().getRegClass(TripCount->getReg());
    unsigned CountReg = MF->getRegInfo().createVirtualRegister(RC);
    BuildMI(*Preheader, InsertPos, InsertPos->getDebugLoc(),
            TII->get(TargetOpcode::COPY), CountReg).addReg(TripCount->getReg());
    if (TripCount->isNeg()) {
      unsigned CountReg1 = CountReg;
      CountReg = MF->getRegInfo().createVirtualRegister(RC);
      BuildMI(*Preheader, InsertPos, InsertPos->getDebugLoc(),
              TII->get(Hexagon::NEG), CountReg).addReg(CountReg1);
    }

    // Add the Loop instruction to the begining of the loop.
    BuildMI(*Preheader, InsertPos, InsertPos->getDebugLoc(),
            TII->get(Hexagon::LOOP0_r)).addMBB(LoopStart).addReg(CountReg);
  } else {
    assert(TripCount->isImm() && "Expecting immedate vaule for trip count");
    // Add the Loop immediate instruction to the beginning of the loop.
    int64_t CountImm = TripCount->getImm();
    BuildMI(*Preheader, InsertPos, InsertPos->getDebugLoc(),
            TII->get(Hexagon::LOOP0_i)).addMBB(LoopStart).addImm(CountImm);
  }

  // Make sure the loop start always has a reference in the CFG.  We need to
  // create a BlockAddress operand to get this mechanism to work both the
  // MachineBasicBlock and BasicBlock objects need the flag set.
  LoopStart->setHasAddressTaken();
  // This line is needed to set the hasAddressTaken flag on the BasicBlock
  // object
  BlockAddress::get(const_cast<BasicBlock *>(LoopStart->getBasicBlock()));

  // Replace the loop branch with an endloop instruction.
  DebugLoc dl = LastI->getDebugLoc();
  BuildMI(*LastMBB, LastI, dl, TII->get(Hexagon::ENDLOOP0)).addMBB(LoopStart);

  // The loop ends with either:
  //  - a conditional branch followed by an unconditional branch, or
  //  - a conditional branch to the loop start.
  if (LastI->getOpcode() == Hexagon::JMP_c ||
      LastI->getOpcode() == Hexagon::JMP_cNot) {
    // delete one and change/add an uncond. branch to out of the loop
    MachineBasicBlock *BranchTarget = LastI->getOperand(1).getMBB();
    LastI = LastMBB->erase(LastI);
    if (!L->contains(BranchTarget)) {
      if (LastI != LastMBB->end()) {
        TII->RemoveBranch(*LastMBB);
      }
      SmallVector<MachineOperand, 0> Cond;
      TII->InsertBranch(*LastMBB, BranchTarget, 0, Cond, dl);
    }
  } else {
    // Conditional branch to loop start; just delete it.
    LastMBB->erase(LastI);
  }
  delete TripCount;

  ++NumHWLoops;
  return true;
}