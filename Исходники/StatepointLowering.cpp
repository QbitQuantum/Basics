void SelectionDAGBuilder::visitGCResult(const CallInst &CI) {
  // The result value of the gc_result is simply the result of the actual
  // call.  We've already emitted this, so just grab the value.
  Instruction *I = cast<Instruction>(CI.getArgOperand(0));
  assert(isStatepoint(I) && "first argument must be a statepoint token");

  if (I->getParent() != CI.getParent()) {
    // Statepoint is in different basic block so we should have stored call
    // result in a virtual register.
    // We can not use default getValue() functionality to copy value from this
    // register because statepoint and actuall call return types can be
    // different, and getValue() will use CopyFromReg of the wrong type,
    // which is always i32 in our case.
    PointerType *CalleeType = cast<PointerType>(
        ImmutableStatepoint(I).getCalledValue()->getType());
    Type *RetTy =
        cast<FunctionType>(CalleeType->getElementType())->getReturnType();
    SDValue CopyFromReg = getCopyFromRegs(I, RetTy);

    assert(CopyFromReg.getNode());
    setValue(&CI, CopyFromReg);
  } else {
    setValue(&CI, getValue(I));
  }
}