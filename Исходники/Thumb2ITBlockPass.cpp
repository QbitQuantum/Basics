bool Thumb2ITBlockPass::InsertITInstructions(MachineBasicBlock &MBB) {
  bool Modified = false;

  SmallSet<unsigned, 4> Defs;
  SmallSet<unsigned, 4> Uses;
  MachineBasicBlock::iterator MBBI = MBB.begin(), E = MBB.end();
  while (MBBI != E) {
    MachineInstr *MI = &*MBBI;
    DebugLoc dl = MI->getDebugLoc();
    unsigned PredReg = 0;
    ARMCC::CondCodes CC = getPredicate(MI, PredReg);
    if (CC == ARMCC::AL) {
      ++MBBI;
      continue;
    }

    Defs.clear();
    Uses.clear();
    TrackDefUses(MI, Defs, Uses);

    // Insert an IT instruction.
    MachineInstrBuilder MIB = BuildMI(MBB, MBBI, dl, TII->get(ARM::t2IT))
      .addImm(CC);
    MachineBasicBlock::iterator InsertPos = MIB;
    ++MBBI;

    // Finalize IT mask.
    ARMCC::CondCodes OCC = ARMCC::getOppositeCondition(CC);
    unsigned Mask = 0, Pos = 3;
    // Branches, including tricky ones like LDM_RET, need to end an IT
    // block so check the instruction we just put in the block.
    for (; MBBI != E && Pos &&
           (!MI->getDesc().isBranch() && !MI->getDesc().isReturn()) ; ++MBBI) {
      if (MBBI->isDebugValue())
        continue;

      MachineInstr *NMI = &*MBBI;
      MI = NMI;

      unsigned NPredReg = 0;
      ARMCC::CondCodes NCC = getPredicate(NMI, NPredReg);
      if (NCC == CC || NCC == OCC)
        Mask |= (NCC & 1) << Pos;
      else {
        unsigned SrcReg, DstReg, SrcSubIdx, DstSubIdx;
        if (NCC == ARMCC::AL &&
            TII->isMoveInstr(*NMI, SrcReg, DstReg, SrcSubIdx, DstSubIdx)) {
          assert(SrcSubIdx == 0 && DstSubIdx == 0 &&
                 "Sub-register indices still around?");
          // llvm models select's as two-address instructions. That means a copy
          // is inserted before a t2MOVccr, etc. If the copy is scheduled in
          // between selects we would end up creating multiple IT blocks.
          if (!Uses.count(DstReg) && !Defs.count(SrcReg)) {
            --MBBI;
            MBB.remove(NMI);
            MBB.insert(InsertPos, NMI);
            ++NumMovedInsts;
            continue;
          }
        }
        break;
      }
      TrackDefUses(NMI, Defs, Uses);
      --Pos;
    }

    Mask |= (1 << Pos);
    // Tag along (firstcond[0] << 4) with the mask.
    Mask |= (CC & 1) << 4;
    MIB.addImm(Mask);
    Modified = true;
    ++NumITs;
  }

  return Modified;
}