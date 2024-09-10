void ForwardControlFlowIntegrity::rewriteFunctionPointer(
    Module &M, Instruction *I, Value *FunPtr, Constant *JumpTableStart,
    Constant *JumpTableMask, Constant *JumpTableSize) {
  IRBuilder<> TempBuilder(I);

  Type *OrigFunType = FunPtr->getType();

  BasicBlock *CurBB = cast<BasicBlock>(I->getParent());
  Function *CurF = cast<Function>(CurBB->getParent());
  Type *Int64Ty = Type::getInt64Ty(M.getContext());

  Value *TI = TempBuilder.CreatePtrToInt(FunPtr, Int64Ty);
  Value *TStartInt = TempBuilder.CreatePtrToInt(JumpTableStart, Int64Ty);

  Value *NewFunPtr = nullptr;
  Value *Check = nullptr;
  switch (CFIType) {
  case CFIntegrity::Sub: {
    // This is the subtract, mask, and add version.
    // Subtract from the base.
    Value *Sub = TempBuilder.CreateSub(TI, TStartInt);

    // Mask the difference to force this to be a table offset.
    Value *And = TempBuilder.CreateAnd(Sub, JumpTableMask);

    // Add it back to the base.
    Value *Result = TempBuilder.CreateAdd(And, TStartInt);

    // Convert it back into a function pointer that we can call.
    NewFunPtr = TempBuilder.CreateIntToPtr(Result, OrigFunType);
    break;
  }
  case CFIntegrity::Ror: {
    // This is the subtract and rotate version.
    // Rotate right by the alignment value. The optimizer should recognize
    // this sequence as a rotation.

    // This cast is safe, since unsigned is always a subset of uint64_t.
    uint64_t LogByteAlignment64 = static_cast<uint64_t>(LogByteAlignment);
    Constant *RightShift = ConstantInt::get(Int64Ty, LogByteAlignment64);
    Constant *LeftShift = ConstantInt::get(Int64Ty, 64 - LogByteAlignment64);

    // Subtract from the base.
    Value *Sub = TempBuilder.CreateSub(TI, TStartInt);

    // Create the equivalent of a rotate-right instruction.
    Value *Shr = TempBuilder.CreateLShr(Sub, RightShift);
    Value *Shl = TempBuilder.CreateShl(Sub, LeftShift);
    Value *Or = TempBuilder.CreateOr(Shr, Shl);

    // Perform unsigned comparison to check for inclusion in the table.
    Check = TempBuilder.CreateICmpULT(Or, JumpTableSize);
    NewFunPtr = FunPtr;
    break;
  }
  case CFIntegrity::Add: {
    // This is the mask and add version.
    // Mask the function pointer to turn it into an offset into the table.
    Value *And = TempBuilder.CreateAnd(TI, JumpTableMask);

    // Then or this offset to the base and get the pointer value.
    Value *Result = TempBuilder.CreateAdd(And, TStartInt);

    // Convert it back into a function pointer that we can call.
    NewFunPtr = TempBuilder.CreateIntToPtr(Result, OrigFunType);
    break;
  }
  }

  if (!CFIEnforcing) {
    // If a check hasn't been added (in the rotation version), then check to see
    // if it's the same as the original function. This check determines whether
    // or not we call the CFI failure function.
    if (!Check)
      Check = TempBuilder.CreateICmpEQ(NewFunPtr, FunPtr);
    BasicBlock *InvalidPtrBlock =
        BasicBlock::Create(M.getContext(), "invalid.ptr", CurF, 0);
    BasicBlock *ContinuationBB = CurBB->splitBasicBlock(I);

    // Remove the unconditional branch that connects the two blocks.
    TerminatorInst *TermInst = CurBB->getTerminator();
    TermInst->eraseFromParent();

    // Add a conditional branch that depends on the Check above.
    BranchInst::Create(ContinuationBB, InvalidPtrBlock, Check, CurBB);

    // Call the warning function for this pointer, then continue.
    Instruction *BI = BranchInst::Create(ContinuationBB, InvalidPtrBlock);
    insertWarning(M, InvalidPtrBlock, BI, FunPtr);
  } else {
    // Modify the instruction to call this value.
    CallSite CS(I);
    CS.setCalledFunction(NewFunPtr);
  }
}