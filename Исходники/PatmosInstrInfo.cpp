unsigned PatmosInstrInfo::moveUp(MachineBasicBlock &MBB,
                                 MachineBasicBlock::iterator &II,
                                 unsigned Cycles) const
{
  // TODO We assume here that we do not have instructions which must be scheduled
  // *within* a certain amount of cycles, except for branches (i.e., we
  // do not emit overlapping pipelined MULs). Otherwise we would need to
  // check if we violate any latency constraints when inserting an instruction

  // Note: We assume that the instruction has no dependencies on previous
  // instructions within the given number of cycles. If we would check for this,
  // this would become a complete scheduler.

  // We might move an instruction
  // 1) outside of delay slots -> always possible
  // 2) into a delay slot -> optional, must add predicate and replace NOP or
  //    be bundled; we do not move other instructions around
  // 3) over a branch -> always possible if not predicated, but only until next
  //    delay slot and if not moved into a delay slot

  if (II->isBundled()) {
    // TODO moving bundled instructions is not yet supported.
    return Cycles;
  }

  MachineBasicBlock::iterator J = II;

  // determine start of first delay slot above the instruction
  int nonDelayed = findPrevDelaySlotEnd(MBB, J, Cycles);

  // Check if the instruction is inside a delay slot
  if (nonDelayed < 0) {
    // do not move it out of the delay slot
    // TODO we could move it, and insert a NOP instead..
    return Cycles;
  }

  bool isBranch = II->isBranch();
  bool isCFLInstr = isBranch || II->isCall() || II->isReturn();

  if (nonDelayed < (int)Cycles && J->isBranch() &&
      !isPredicated(&*II) && isPredicated(&*J) &&
      (!isCFLInstr || (isBranch && PST.allowBranchInsideCFLDelaySots()) ))
  {
    // J points to the branch instruction
    unsigned delayed = nonDelayed + PST.getDelaySlotCycles(&*J) + 1;

    // Load the predicate of the branch
    // We assume here that a bundle only contains at most one branch,
    // that this instruction is the first instruction in the bundle, and
    // that the branch is actually predicated.
    // TODO add a check for this!
    SmallVector<MachineOperand,4> Pred;

    const MachineInstr *BR = getFirstMI(&*J);
    assert(BR->isBranch() && "Branch is not in the first slot");

    getPredicateOperands(BR, Pred);
    assert(Pred.size() >= 2 && "Branch instruction not predicated");

    // determine if instruction might be moved over the delay slot
    if (delayed <= Cycles) {

      // TODO We only move the instruction at most one cycle above the branch.
      //      We could move it further up, but then we need to check where the
      //      predicate is defined.
      MachineBasicBlock::iterator JJ = J;
      if (findPrevDelaySlotEnd(MBB, JJ, 0) >= 0) {

        // Move the instruction up and predicate it
        II = MBB.insert(J, MBB.remove(II));

        PredicateInstruction(&*II, Pred);
        NegatePredicate(&*II);

        return Cycles - delayed;
      }
    }

    // if not, check if we can move it into the delay slot
    MachineBasicBlock::iterator dst = J;

    // Going down from the branch until the first possible slot, checking
    // that the predicate is not redefined.
    // Note that we are not inserting the instruction, but replacing an
    // instruction, i.e., we move one instruction less over II than in the
    // other cases.
    while ((int)delayed > nonDelayed) {
      delayed--;

      if (delayed <= Cycles && moveTo(MBB, dst, II, &Pred, true)) {
        return Cycles - delayed;
      }

      // TODO check if this also finds a MTS $S0 !!
      if (dst->definesRegister(Pred[0].getReg(), &getRegisterInfo())) {
        break;
      }

      dst = nextNonPseudo(MBB, dst);
    }
  }

  if (nonDelayed > 0) {
    // we are staying below a delay slot, just move the instruction up
    J = II;
    recedeCycles(MBB, J, nonDelayed);

    II = MBB.insert(J, MBB.remove(II));

    return Cycles - nonDelayed;
  }

  return Cycles;
}