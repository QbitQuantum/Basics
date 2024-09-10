/// Update the callsite to pass in the correct arguments.
static void rewriteApplyInst(const CallSiteDescriptor &CSDesc,
                             SILFunction *NewF) {
  FullApplySite AI = CSDesc.getApplyInst();
  SILInstruction *Closure = CSDesc.getClosure();
  SILBuilderWithScope Builder(Closure);
  FunctionRefInst *FRI = Builder.createFunctionRef(AI.getLoc(), NewF);

  // Create the args for the new apply by removing the closure argument...
  llvm::SmallVector<SILValue, 8> NewArgs;
  unsigned Index = 0;
  for (auto Arg : AI.getArguments()) {
    if (Index != CSDesc.getClosureIndex())
      NewArgs.push_back(Arg);
    Index++;
  }

  // ... and appending the captured arguments. We also insert retains here at
  // the location of the original closure. This is needed to balance the
  // implicit release of all captured arguments that occurs when the partial
  // apply is destroyed.
  SILModule &M = NewF->getModule();
  for (auto Arg : CSDesc.getArguments()) {
    NewArgs.push_back(Arg);

    SILType ArgTy = Arg->getType();

    // If our argument is of trivial type, continue...
    if (ArgTy.isTrivial(M))
      continue;

    // TODO: When we support address types, this code path will need to be
    // updated.

    // We need to balance the consumed argument of the new partial_apply in the
    // specialized callee by a retain. If both the original partial_apply and
    // the apply of the callee are in the same basic block we can assume they
    // are executed the same number of times. Therefore it is sufficient to just
    // retain the argument at the site of the original partial_apply.
    //
    //    %closure = partial_apply (%arg)
    //             = apply %callee(%closure)
    //  =>
    //             retain %arg
    //    %closure = partial_apply (%arg)
    //               apply %specialized_callee(..., %arg)
    //
    // However, if they are not in the same basic block the callee might be
    // executed more frequently than the closure (for example, if the closure is
    // created in a loop preheader and the callee taking the closure is executed
    // in the loop). In such a case we must keep the argument live across the
    // call site of the callee and emit a matching retain for every invocation
    // of the callee.
    //
    //    %closure = partial_apply (%arg)
    //
    //    while () {
    //             = %callee(%closure)
    //    }
    // =>
    //               retain %arg
    //    %closure = partial_apply (%arg)
    //
    //    while () {
    //               retain %arg
    //               apply %specialized_callee(.., %arg)
    //    }
    //               release %arg
    //
    if (AI.getParent() != Closure->getParent()) {
      // Emit the retain and release that keeps the argument life across the
      // callee using the closure.
      CSDesc.extendArgumentLifetime(Arg);

      // Emit the retain that matches the captured argument by the partial_apply
      // in the callee that is consumed by the partial_apply.
      Builder.setInsertionPoint(AI.getInstruction());
      Builder.createRetainValue(Closure->getLoc(), Arg, Atomicity::Atomic);
    } else {
      Builder.createRetainValue(Closure->getLoc(), Arg, Atomicity::Atomic);
    }
  }

  SILType LoweredType = NewF->getLoweredType();
  SILType ResultType = LoweredType.castTo<SILFunctionType>()->getSILResult();
  Builder.setInsertionPoint(AI.getInstruction());
  FullApplySite NewAI;
  if (auto *TAI = dyn_cast<TryApplyInst>(AI)) {
    NewAI = Builder.createTryApply(AI.getLoc(), FRI, LoweredType,
                                   ArrayRef<Substitution>(),
                                   NewArgs,
                                   TAI->getNormalBB(), TAI->getErrorBB());
    // If we passed in the original closure as @owned, then insert a release
    // right after NewAI. This is to balance the +1 from being an @owned
    // argument to AI.
    if (CSDesc.isClosureConsumed() && CSDesc.closureHasRefSemanticContext()) {
      Builder.setInsertionPoint(TAI->getNormalBB()->begin());
      Builder.createReleaseValue(Closure->getLoc(), Closure, Atomicity::Atomic);
      Builder.setInsertionPoint(TAI->getErrorBB()->begin());
      Builder.createReleaseValue(Closure->getLoc(), Closure, Atomicity::Atomic);
      Builder.setInsertionPoint(AI.getInstruction());
    }
  } else {
    NewAI = Builder.createApply(AI.getLoc(), FRI, LoweredType,
                                ResultType, ArrayRef<Substitution>(),
                                NewArgs, cast<ApplyInst>(AI)->isNonThrowing());
    // If we passed in the original closure as @owned, then insert a release
    // right after NewAI. This is to balance the +1 from being an @owned
    // argument to AI.
    if (CSDesc.isClosureConsumed() && CSDesc.closureHasRefSemanticContext())
      Builder.createReleaseValue(Closure->getLoc(), Closure, Atomicity::Atomic);
  }

  // Replace all uses of the old apply with the new apply.
  if (isa<ApplyInst>(AI))
    AI.getInstruction()->replaceAllUsesWith(NewAI.getInstruction());
  // Erase the old apply.
  AI.getInstruction()->eraseFromParent();

  // TODO: Maybe include invalidation code for CallSiteDescriptor after we erase
  // AI from parent?
}