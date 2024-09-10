/// It's possible to determine the value of a register based on a dominating
/// condition.  To do so, this function checks to see if the basic block \p MBB
/// is the target of a conditional branch \p CondBr with an equality comparison.
/// If the branch is a CBZ/CBNZ, we know the value of its source operand is zero
/// in \p MBB for some cases.  Otherwise, we find and inspect the NZCV setting
/// instruction (e.g., SUBS, ADDS).  If this instruction defines a register
/// other than WZR/XZR, we know the value of the destination register is zero in
/// \p MMB for some cases.  In addition, if the NZCV setting instruction is
/// comparing against a constant we know the other source register is equal to
/// the constant in \p MBB for some cases.  If we find any constant values, push
/// a physical register and constant value pair onto the KnownRegs vector and
/// return true.  Otherwise, return false if no known values were found.
bool AArch64RedundantCopyElimination::knownRegValInBlock(
    MachineInstr &CondBr, MachineBasicBlock *MBB,
    SmallVectorImpl<RegImm> &KnownRegs, MachineBasicBlock::iterator &FirstUse) {
  unsigned Opc = CondBr.getOpcode();

  // Check if the current basic block is the target block to which the
  // CBZ/CBNZ instruction jumps when its Wt/Xt is zero.
  if (((Opc == AArch64::CBZW || Opc == AArch64::CBZX) &&
       MBB == CondBr.getOperand(1).getMBB()) ||
      ((Opc == AArch64::CBNZW || Opc == AArch64::CBNZX) &&
       MBB != CondBr.getOperand(1).getMBB())) {
    FirstUse = CondBr;
    KnownRegs.push_back(RegImm(CondBr.getOperand(0).getReg(), 0));
    return true;
  }

  // Otherwise, must be a conditional branch.
  if (Opc != AArch64::Bcc)
    return false;

  // Must be an equality check (i.e., == or !=).
  AArch64CC::CondCode CC = (AArch64CC::CondCode)CondBr.getOperand(0).getImm();
  if (CC != AArch64CC::EQ && CC != AArch64CC::NE)
    return false;

  MachineBasicBlock *BrTarget = CondBr.getOperand(1).getMBB();
  if ((CC == AArch64CC::EQ && BrTarget != MBB) ||
      (CC == AArch64CC::NE && BrTarget == MBB))
    return false;

  // Stop if we get to the beginning of PredMBB.
  MachineBasicBlock *PredMBB = *MBB->pred_begin();
  assert(PredMBB == CondBr.getParent() &&
         "Conditional branch not in predecessor block!");
  if (CondBr == PredMBB->begin())
    return false;

  // Registers clobbered in PredMBB between CondBr instruction and current
  // instruction being checked in loop.
  DomBBClobberedRegs.reset();

  // Find compare instruction that sets NZCV used by CondBr.
  MachineBasicBlock::reverse_iterator RIt = CondBr.getReverseIterator();
  for (MachineInstr &PredI : make_range(std::next(RIt), PredMBB->rend())) {

    bool IsCMN = false;
    switch (PredI.getOpcode()) {
    default:
      break;

    // CMN is an alias for ADDS with a dead destination register.
    case AArch64::ADDSWri:
    case AArch64::ADDSXri:
      IsCMN = true;
      LLVM_FALLTHROUGH;
    // CMP is an alias for SUBS with a dead destination register.
    case AArch64::SUBSWri:
    case AArch64::SUBSXri: {
      MCPhysReg DstReg = PredI.getOperand(0).getReg();
      MCPhysReg SrcReg = PredI.getOperand(1).getReg();

      bool Res = false;
      // If we're comparing against a non-symbolic immediate and the source
      // register of the compare is not modified (including a self-clobbering
      // compare) between the compare and conditional branch we known the value
      // of the 1st source operand.
      if (PredI.getOperand(2).isImm() && !DomBBClobberedRegs[SrcReg] &&
          SrcReg != DstReg) {
        // We've found the instruction that sets NZCV.
        int32_t KnownImm = PredI.getOperand(2).getImm();
        int32_t Shift = PredI.getOperand(3).getImm();
        KnownImm <<= Shift;
        if (IsCMN)
          KnownImm = -KnownImm;
        FirstUse = PredI;
        KnownRegs.push_back(RegImm(SrcReg, KnownImm));
        Res = true;
      }

      // If this instructions defines something other than WZR/XZR, we know it's
      // result is zero in some cases.
      if (DstReg == AArch64::WZR || DstReg == AArch64::XZR)
        return Res;

      // The destination register must not be modified between the NZCV setting
      // instruction and the conditional branch.
      if (DomBBClobberedRegs[DstReg])
        return Res;

      FirstUse = PredI;
      KnownRegs.push_back(RegImm(DstReg, 0));
      return true;
    }

    // Look for NZCV setting instructions that define something other than
    // WZR/XZR.
    case AArch64::ADCSWr:
    case AArch64::ADCSXr:
    case AArch64::ADDSWrr:
    case AArch64::ADDSWrs:
    case AArch64::ADDSWrx:
    case AArch64::ADDSXrr:
    case AArch64::ADDSXrs:
    case AArch64::ADDSXrx:
    case AArch64::ADDSXrx64:
    case AArch64::ANDSWri:
    case AArch64::ANDSWrr:
    case AArch64::ANDSWrs:
    case AArch64::ANDSXri:
    case AArch64::ANDSXrr:
    case AArch64::ANDSXrs:
    case AArch64::BICSWrr:
    case AArch64::BICSWrs:
    case AArch64::BICSXrs:
    case AArch64::BICSXrr:
    case AArch64::SBCSWr:
    case AArch64::SBCSXr:
    case AArch64::SUBSWrr:
    case AArch64::SUBSWrs:
    case AArch64::SUBSWrx:
    case AArch64::SUBSXrr:
    case AArch64::SUBSXrs:
    case AArch64::SUBSXrx:
    case AArch64::SUBSXrx64: {
      MCPhysReg DstReg = PredI.getOperand(0).getReg();
      if (DstReg == AArch64::WZR || DstReg == AArch64::XZR)
        return false;

      // The destination register of the NZCV setting instruction must not be
      // modified before the conditional branch.
      if (DomBBClobberedRegs[DstReg])
        return false;

      // We've found the instruction that sets NZCV whose DstReg == 0.
      FirstUse = PredI;
      KnownRegs.push_back(RegImm(DstReg, 0));
      return true;
    }
    }

    // Bail if we see an instruction that defines NZCV that we don't handle.
    if (PredI.definesRegister(AArch64::NZCV))
      return false;

    // Track clobbered registers.
    trackRegDefs(PredI, DomBBClobberedRegs, TRI);
  }
  return false;
}