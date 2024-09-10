static void insertBoundsCheck(Value *Or, BuilderTy IRB, GetTrapBBT GetTrapBB) {
  // check if the comparison is always false
  ConstantInt *C = dyn_cast_or_null<ConstantInt>(Or);
  if (C) {
    ++ChecksSkipped;
    // If non-zero, nothing to do.
    if (!C->getZExtValue())
      return;
  }
  ++ChecksAdded;

  BasicBlock::iterator SplitI = IRB.GetInsertPoint();
  BasicBlock *OldBB = SplitI->getParent();
  BasicBlock *Cont = OldBB->splitBasicBlock(SplitI);
  OldBB->getTerminator()->eraseFromParent();

  if (C) {
    // If we have a constant zero, unconditionally branch.
    // FIXME: We should really handle this differently to bypass the splitting
    // the block.
    BranchInst::Create(GetTrapBB(IRB), OldBB);
    return;
  }

  // Create the conditional branch.
  BranchInst::Create(GetTrapBB(IRB), Cont, Or, OldBB);
}