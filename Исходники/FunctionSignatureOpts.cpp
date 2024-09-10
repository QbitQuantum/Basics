void FunctionSignatureTransform::createFunctionSignatureOptimizedFunction() {
  // Create the optimized function !
  SILModule &M = F->getModule();
  std::string Name = createOptimizedSILFunctionName();
  SILLinkage linkage = F->getLinkage();
  if (isAvailableExternally(linkage))
    linkage = SILLinkage::Shared;

  DEBUG(llvm::dbgs() << "  -> create specialized function " << Name << "\n");

  NewF = M.createFunction(linkage, Name, createOptimizedSILFunctionType(),
                          F->getGenericEnvironment(), F->getLocation(),
                          F->isBare(), F->isTransparent(), F->isSerialized(),
                          F->isThunk(), F->getClassVisibility(),
                          F->getInlineStrategy(), F->getEffectsKind(), nullptr,
                          F->getDebugScope());
  if (F->hasUnqualifiedOwnership()) {
    NewF->setUnqualifiedOwnership();
  }

  // Then we transfer the body of F to NewF.
  NewF->spliceBody(F);

  // Array semantic clients rely on the signature being as in the original
  // version.
  for (auto &Attr : F->getSemanticsAttrs()) {
    if (!StringRef(Attr).startswith("array."))
      NewF->addSemanticsAttr(Attr);
  }

  // Do the last bit of work to the newly created optimized function.
  ArgumentExplosionFinalizeOptimizedFunction();
  DeadArgumentFinalizeOptimizedFunction();

  // Create the thunk body !
  F->setThunk(IsThunk);
  // The thunk now carries the information on how the signature is
  // optimized. If we inline the thunk, we will get the benefit of calling
  // the signature optimized function without additional setup on the
  // caller side.
  F->setInlineStrategy(AlwaysInline);
  SILBasicBlock *ThunkBody = F->createBasicBlock();
  for (auto &ArgDesc : ArgumentDescList) {
    ThunkBody->createFunctionArgument(ArgDesc.Arg->getType(), ArgDesc.Decl);
  }

  SILLocation Loc = ThunkBody->getParent()->getLocation();
  SILBuilder Builder(ThunkBody);
  Builder.setCurrentDebugScope(ThunkBody->getParent()->getDebugScope());

  FunctionRefInst *FRI = Builder.createFunctionRef(Loc, NewF);

  // Create the args for the thunk's apply, ignoring any dead arguments.
  llvm::SmallVector<SILValue, 8> ThunkArgs;
  for (auto &ArgDesc : ArgumentDescList) {
    addThunkArgument(ArgDesc, Builder, ThunkBody, ThunkArgs);
  }

  // We are ignoring generic functions and functions with out parameters for
  // now.
  SILValue ReturnValue;
  SILType LoweredType = NewF->getLoweredType();
  SILType ResultType = NewF->getConventions().getSILResultType();
  auto FunctionTy = LoweredType.castTo<SILFunctionType>();
  if (FunctionTy->hasErrorResult()) {
    // We need a try_apply to call a function with an error result.
    SILFunction *Thunk = ThunkBody->getParent();
    SILBasicBlock *NormalBlock = Thunk->createBasicBlock();
    ReturnValue =
        NormalBlock->createPHIArgument(ResultType, ValueOwnershipKind::Owned);
    SILBasicBlock *ErrorBlock = Thunk->createBasicBlock();
    SILType Error =
        SILType::getPrimitiveObjectType(FunctionTy->getErrorResult().getType());
    auto *ErrorArg =
        ErrorBlock->createPHIArgument(Error, ValueOwnershipKind::Owned);
    Builder.createTryApply(Loc, FRI, LoweredType, SubstitutionList(),
                           ThunkArgs, NormalBlock, ErrorBlock);

    Builder.setInsertionPoint(ErrorBlock);
    Builder.createThrow(Loc, ErrorArg);
    Builder.setInsertionPoint(NormalBlock);
  } else {
    ReturnValue = Builder.createApply(Loc, FRI, LoweredType, ResultType,
                                      SubstitutionList(), ThunkArgs,
                                      false);
  }

  // Set up the return results.
  if (NewF->isNoReturnFunction()) {
    Builder.createUnreachable(Loc);
  } else {
    Builder.createReturn(Loc, ReturnValue);
  }

  // Do the last bit work to finalize the thunk.
  OwnedToGuaranteedFinalizeThunkFunction(Builder, F);
  assert(F->getDebugScope()->Parent != NewF->getDebugScope()->Parent);
}