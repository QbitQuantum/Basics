/// Return true if MI is likely to be usable as a memory operation by the
/// implicit null check optimization.
///
/// This is a "best effort" heuristic, and should not be relied upon for
/// correctness.  This returning true does not guarantee that the implicit null
/// check optimization is legal over MI, and this returning false does not
/// guarantee MI cannot possibly be used to do a null check.
static bool SinkingPreventsImplicitNullCheck(MachineInstr &MI,
                                             const TargetInstrInfo *TII,
                                             const TargetRegisterInfo *TRI) {
  using MachineBranchPredicate = TargetInstrInfo::MachineBranchPredicate;

  auto *MBB = MI.getParent();
  if (MBB->pred_size() != 1)
    return false;

  auto *PredMBB = *MBB->pred_begin();
  auto *PredBB = PredMBB->getBasicBlock();

  // Frontends that don't use implicit null checks have no reason to emit
  // branches with make.implicit metadata, and this function should always
  // return false for them.
  if (!PredBB ||
      !PredBB->getTerminator()->getMetadata(LLVMContext::MD_make_implicit))
    return false;

  unsigned BaseReg;
  int64_t Offset;
  if (!TII->getMemOpBaseRegImmOfs(MI, BaseReg, Offset, TRI))
    return false;

  if (!(MI.mayLoad() && !MI.isPredicable()))
    return false;

  MachineBranchPredicate MBP;
  if (TII->analyzeBranchPredicate(*PredMBB, MBP, false))
    return false;

  return MBP.LHS.isReg() && MBP.RHS.isImm() && MBP.RHS.getImm() == 0 &&
         (MBP.Predicate == MachineBranchPredicate::PRED_NE ||
          MBP.Predicate == MachineBranchPredicate::PRED_EQ) &&
         MBP.LHS.getReg() == BaseReg;
}