/// fixupConditionalBranch - Fix up a conditional branch whose destination is
/// too far away to fit in its displacement field. It is converted to an inverse
/// conditional branch + an unconditional branch to the destination.
bool BranchRelaxation::fixupConditionalBranch(MachineInstr &MI) {
  DebugLoc DL = MI.getDebugLoc();
  MachineBasicBlock *MBB = MI.getParent();
  MachineBasicBlock *TBB = nullptr, *FBB = nullptr;
  MachineBasicBlock *NewBB = nullptr;
  SmallVector<MachineOperand, 4> Cond;

  auto insertUncondBranch = [&](MachineBasicBlock *MBB,
                                MachineBasicBlock *DestBB) {
    unsigned &BBSize = BlockInfo[MBB->getNumber()].Size;
    int NewBrSize = 0;
    TII->insertUnconditionalBranch(*MBB, DestBB, DL, &NewBrSize);
    BBSize += NewBrSize;
  };
  auto insertBranch = [&](MachineBasicBlock *MBB, MachineBasicBlock *TBB,
                          MachineBasicBlock *FBB,
                          SmallVectorImpl<MachineOperand>& Cond) {
    unsigned &BBSize = BlockInfo[MBB->getNumber()].Size;
    int NewBrSize = 0;
    TII->insertBranch(*MBB, TBB, FBB, Cond, DL, &NewBrSize);
    BBSize += NewBrSize;
  };
  auto removeBranch = [&](MachineBasicBlock *MBB) {
    unsigned &BBSize = BlockInfo[MBB->getNumber()].Size;
    int RemovedSize = 0;
    TII->removeBranch(*MBB, &RemovedSize);
    BBSize -= RemovedSize;
  };

  auto finalizeBlockChanges = [&](MachineBasicBlock *MBB,
                                  MachineBasicBlock *NewBB) {
    // Keep the block offsets up to date.
    adjustBlockOffsets(*MBB);

    // Need to fix live-in lists if we track liveness.
    if (NewBB && TRI->trackLivenessAfterRegAlloc(*MF))
      computeAndAddLiveIns(LiveRegs, *NewBB);
  };

  bool Fail = TII->analyzeBranch(*MBB, TBB, FBB, Cond);
  assert(!Fail && "branches to be relaxed must be analyzable");
  (void)Fail;

  // Add an unconditional branch to the destination and invert the branch
  // condition to jump over it:
  // tbz L1
  // =>
  // tbnz L2
  // b   L1
  // L2:

  bool ReversedCond = !TII->reverseBranchCondition(Cond);
  if (ReversedCond) {
    if (FBB && isBlockInRange(MI, *FBB)) {
      // Last MI in the BB is an unconditional branch. We can simply invert the
      // condition and swap destinations:
      // beq L1
      // b   L2
      // =>
      // bne L2
      // b   L1
      LLVM_DEBUG(dbgs() << "  Invert condition and swap "
                           "its destination with "
                        << MBB->back());

      removeBranch(MBB);
      insertBranch(MBB, FBB, TBB, Cond);
      finalizeBlockChanges(MBB, nullptr);
      return true;
    }
    if (FBB) {
      // We need to split the basic block here to obtain two long-range
      // unconditional branches.
      NewBB = createNewBlockAfter(*MBB);

      insertUncondBranch(NewBB, FBB);
      // Update the succesor lists according to the transformation to follow.
      // Do it here since if there's no split, no update is needed.
      MBB->replaceSuccessor(FBB, NewBB);
      NewBB->addSuccessor(FBB);
    }

    // We now have an appropriate fall-through block in place (either naturally or
    // just created), so we can use the inverted the condition.
    MachineBasicBlock &NextBB = *std::next(MachineFunction::iterator(MBB));

    LLVM_DEBUG(dbgs() << "  Insert B to " << printMBBReference(*TBB)
                      << ", invert condition and change dest. to "
                      << printMBBReference(NextBB) << '\n');

    removeBranch(MBB);
    // Insert a new conditional branch and a new unconditional branch.
    insertBranch(MBB, &NextBB, TBB, Cond);

    finalizeBlockChanges(MBB, NewBB);
    return true;
  }
  // Branch cond can't be inverted.
  // In this case we always add a block after the MBB.
  LLVM_DEBUG(dbgs() << "  The branch condition can't be inverted. "
                    << "  Insert a new BB after " << MBB->back());

  if (!FBB)
    FBB = &(*std::next(MachineFunction::iterator(MBB)));

  // This is the block with cond. branch and the distance to TBB is too long.
  //    beq L1
  // L2:

  // We do the following transformation:
  //    beq NewBB
  //    b L2
  // NewBB:
  //    b L1
  // L2:

  NewBB = createNewBlockAfter(*MBB);
  insertUncondBranch(NewBB, TBB);

  LLVM_DEBUG(dbgs() << "  Insert cond B to the new BB "
                    << printMBBReference(*NewBB)
                    << "  Keep the exiting condition.\n"
                    << "  Insert B to " << printMBBReference(*FBB) << ".\n"
                    << "  In the new BB: Insert B to "
                    << printMBBReference(*TBB) << ".\n");

  // Update the successor lists according to the transformation to follow.
  MBB->replaceSuccessor(TBB, NewBB);
  NewBB->addSuccessor(TBB);

  // Replace branch in the current (MBB) block.
  removeBranch(MBB);
  insertBranch(MBB, NewBB, FBB, Cond);

  finalizeBlockChanges(MBB, NewBB);
  return true;
}