Value *PHITransAddr::PHITranslateSubExpr(Value *V, BasicBlock *CurBB,
                                         BasicBlock *PredBB,
                                         const DominatorTree *DT) {
  // If this is a non-instruction value, it can't require PHI translation.
  Instruction *Inst = dyn_cast<Instruction>(V);
  if (!Inst) return V;

  // Determine whether 'Inst' is an input to our PHI translatable expression.
  bool isInput =
      std::find(InstInputs.begin(), InstInputs.end(), Inst) != InstInputs.end();

  // Handle inputs instructions if needed.
  if (isInput) {
    if (Inst->getParent() != CurBB) {
      // If it is an input defined in a different block, then it remains an
      // input.
      return Inst;
    }

    // If 'Inst' is defined in this block and is an input that needs to be phi
    // translated, we need to incorporate the value into the expression or fail.

    // In either case, the instruction itself isn't an input any longer.
    InstInputs.erase(std::find(InstInputs.begin(), InstInputs.end(), Inst));

    // If this is a PHI, go ahead and translate it.
    if (PHINode *PN = dyn_cast<PHINode>(Inst))
      return AddAsInput(PN->getIncomingValueForBlock(PredBB));

    // If this is a non-phi value, and it is analyzable, we can incorporate it
    // into the expression by making all instruction operands be inputs.
    if (!CanPHITrans(Inst))
      return nullptr;

    // All instruction operands are now inputs (and of course, they may also be
    // defined in this block, so they may need to be phi translated themselves.
    for (unsigned i = 0, e = Inst->getNumOperands(); i != e; ++i)
      if (Instruction *Op = dyn_cast<Instruction>(Inst->getOperand(i)))
        InstInputs.push_back(Op);
  }

  // Ok, it must be an intermediate result (either because it started that way
  // or because we just incorporated it into the expression).  See if its
  // operands need to be phi translated, and if so, reconstruct it.

  if (CastInst *Cast = dyn_cast<CastInst>(Inst)) {
    if (!isSafeToSpeculativelyExecute(Cast)) return nullptr;
    Value *PHIIn = PHITranslateSubExpr(Cast->getOperand(0), CurBB, PredBB, DT);
    if (!PHIIn) return nullptr;
    if (PHIIn == Cast->getOperand(0))
      return Cast;

    // Find an available version of this cast.

    // Constants are trivial to find.
    if (Constant *C = dyn_cast<Constant>(PHIIn))
      return AddAsInput(ConstantExpr::getCast(Cast->getOpcode(),
                                              C, Cast->getType()));

    // Otherwise we have to see if a casted version of the incoming pointer
    // is available.  If so, we can use it, otherwise we have to fail.
    for (User *U : PHIIn->users()) {
      if (CastInst *CastI = dyn_cast<CastInst>(U))
        if (CastI->getOpcode() == Cast->getOpcode() &&
            CastI->getType() == Cast->getType() &&
            (!DT || DT->dominates(CastI->getParent(), PredBB)))
          return CastI;
    }
    return nullptr;
  }

  // Handle getelementptr with at least one PHI translatable operand.
  if (GetElementPtrInst *GEP = dyn_cast<GetElementPtrInst>(Inst)) {
    SmallVector<Value*, 8> GEPOps;
    bool AnyChanged = false;
    for (unsigned i = 0, e = GEP->getNumOperands(); i != e; ++i) {
      Value *GEPOp = PHITranslateSubExpr(GEP->getOperand(i), CurBB, PredBB, DT);
      if (!GEPOp) return nullptr;

      AnyChanged |= GEPOp != GEP->getOperand(i);
      GEPOps.push_back(GEPOp);
    }

    if (!AnyChanged)
      return GEP;

    // Simplify the GEP to handle 'gep x, 0' -> x etc.
    if (Value *V = SimplifyGEPInst(GEP->getSourceElementType(),
                                   GEPOps, DL, TLI, DT, AC)) {
      for (unsigned i = 0, e = GEPOps.size(); i != e; ++i)
        RemoveInstInputs(GEPOps[i], InstInputs);

      return AddAsInput(V);
    }

    // Scan to see if we have this GEP available.
    Value *APHIOp = GEPOps[0];
    for (User *U : APHIOp->users()) {
      if (GetElementPtrInst *GEPI = dyn_cast<GetElementPtrInst>(U))
        if (GEPI->getType() == GEP->getType() &&
            GEPI->getNumOperands() == GEPOps.size() &&
            GEPI->getParent()->getParent() == CurBB->getParent() &&
            (!DT || DT->dominates(GEPI->getParent(), PredBB))) {
          if (std::equal(GEPOps.begin(), GEPOps.end(), GEPI->op_begin()))
            return GEPI;
        }
    }
    return nullptr;
  }

  // Handle add with a constant RHS.
  if (Inst->getOpcode() == Instruction::Add &&
      isa<ConstantInt>(Inst->getOperand(1))) {
    // PHI translate the LHS.
    Constant *RHS = cast<ConstantInt>(Inst->getOperand(1));
    bool isNSW = cast<BinaryOperator>(Inst)->hasNoSignedWrap();
    bool isNUW = cast<BinaryOperator>(Inst)->hasNoUnsignedWrap();

    Value *LHS = PHITranslateSubExpr(Inst->getOperand(0), CurBB, PredBB, DT);
    if (!LHS) return nullptr;

    // If the PHI translated LHS is an add of a constant, fold the immediates.
    if (BinaryOperator *BOp = dyn_cast<BinaryOperator>(LHS))
      if (BOp->getOpcode() == Instruction::Add)
        if (ConstantInt *CI = dyn_cast<ConstantInt>(BOp->getOperand(1))) {
          LHS = BOp->getOperand(0);
          RHS = ConstantExpr::getAdd(RHS, CI);
          isNSW = isNUW = false;

          // If the old 'LHS' was an input, add the new 'LHS' as an input.
          if (std::find(InstInputs.begin(), InstInputs.end(), BOp) !=
              InstInputs.end()) {
            RemoveInstInputs(BOp, InstInputs);
            AddAsInput(LHS);
          }
        }

    // See if the add simplifies away.
    if (Value *Res = SimplifyAddInst(LHS, RHS, isNSW, isNUW, DL, TLI, DT, AC)) {
      // If we simplified the operands, the LHS is no longer an input, but Res
      // is.
      RemoveInstInputs(LHS, InstInputs);
      return AddAsInput(Res);
    }

    // If we didn't modify the add, just return it.
    if (LHS == Inst->getOperand(0) && RHS == Inst->getOperand(1))
      return Inst;

    // Otherwise, see if we have this add available somewhere.
    for (User *U : LHS->users()) {
      if (BinaryOperator *BO = dyn_cast<BinaryOperator>(U))
        if (BO->getOpcode() == Instruction::Add &&
            BO->getOperand(0) == LHS && BO->getOperand(1) == RHS &&
            BO->getParent()->getParent() == CurBB->getParent() &&
            (!DT || DT->dominates(BO->getParent(), PredBB)))
          return BO;
    }

    return nullptr;
  }

  // Otherwise, we failed.
  return nullptr;
}