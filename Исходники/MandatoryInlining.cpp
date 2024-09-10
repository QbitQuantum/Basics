/// \brief Inlines all mandatory inlined functions into the body of a function,
/// first recursively inlining all mandatory apply instructions in those
/// functions into their bodies if necessary.
///
/// \param F the function to be processed
/// \param AI nullptr if this is being called from the top level; the relevant
///   ApplyInst requiring the recursive call when non-null
/// \param FullyInlinedSet the set of all functions already known to be fully
///   processed, to avoid processing them over again
/// \param SetFactory an instance of ImmutableFunctionSet::Factory
/// \param CurrentInliningSet the set of functions currently being inlined in
///   the current call stack of recursive calls
///
/// \returns true if successful, false if failed due to circular inlining.
static bool
runOnFunctionRecursively(SILFunction *F, FullApplySite AI,
                         SILModule::LinkingMode Mode,
                         DenseFunctionSet &FullyInlinedSet,
                         ImmutableFunctionSet::Factory &SetFactory,
                         ImmutableFunctionSet CurrentInliningSet,
                         ClassHierarchyAnalysis *CHA) {
  // Avoid reprocessing functions needlessly.
  if (FullyInlinedSet.count(F))
    return true;

  // Prevent attempt to circularly inline.
  if (CurrentInliningSet.contains(F)) {
    // This cannot happen on a top-level call, so AI should be non-null.
    assert(AI && "Cannot have circular inline without apply");
    SILLocation L = AI.getLoc();
    assert(L && "Must have location for transparent inline apply");
    diagnose(F->getModule().getASTContext(), L.getStartSourceLoc(),
             diag::circular_transparent);
    return false;
  }

  // Add to the current inlining set (immutably, so we only affect the set
  // during this call and recursive subcalls).
  CurrentInliningSet = SetFactory.add(CurrentInliningSet, F);

  SmallVector<SILValue, 16> CaptureArgs;
  SmallVector<SILValue, 32> FullArgs;

  for (auto FI = F->begin(), FE = F->end(); FI != FE; ++FI) {
    for (auto I = FI->begin(), E = FI->end(); I != E; ++I) {
      FullApplySite InnerAI = FullApplySite::isa(&*I);

      if (!InnerAI)
        continue;

      auto *ApplyBlock = InnerAI.getParent();

      auto NewInstPair = tryDevirtualizeApply(InnerAI, CHA);
      if (auto *NewInst = NewInstPair.first) {
        replaceDeadApply(InnerAI, NewInst);
        if (auto *II = dyn_cast<SILInstruction>(NewInst))
          I = II->getIterator();
        else
          I = NewInst->getParentBlock()->begin();
        auto NewAI = FullApplySite::isa(NewInstPair.second.getInstruction());
        if (!NewAI)
          continue;

        InnerAI = NewAI;
      }

      SILLocation Loc = InnerAI.getLoc();
      SILValue CalleeValue = InnerAI.getCallee();
      bool IsThick;
      PartialApplyInst *PAI;
      SILFunction *CalleeFunction = getCalleeFunction(InnerAI, IsThick,
                                                      CaptureArgs, FullArgs,
                                                      PAI,
                                                      Mode);
      if (!CalleeFunction ||
          CalleeFunction->isTransparent() == IsNotTransparent)
        continue;

      if (F->isFragile() &&
          !CalleeFunction->hasValidLinkageForFragileRef()) {
        if (!CalleeFunction->hasValidLinkageForFragileInline()) {
          llvm::errs() << "caller: " << F->getName() << "\n";
          llvm::errs() << "callee: " << CalleeFunction->getName() << "\n";
          llvm_unreachable("Should never be inlining a resilient function into "
                           "a fragile function");
        }
        continue;
      }

      // Then recursively process it first before trying to inline it.
      if (!runOnFunctionRecursively(CalleeFunction, InnerAI, Mode,
                                    FullyInlinedSet, SetFactory,
                                    CurrentInliningSet, CHA)) {
        // If we failed due to circular inlining, then emit some notes to
        // trace back the failure if we have more information.
        // FIXME: possibly it could be worth recovering and attempting other
        // inlines within this same recursive call rather than simply
        // propagating the failure.
        if (AI) {
          SILLocation L = AI.getLoc();
          assert(L && "Must have location for transparent inline apply");
          diagnose(F->getModule().getASTContext(), L.getStartSourceLoc(),
                   diag::note_while_inlining);
        }
        return false;
      }

      // Inline function at I, which also changes I to refer to the first
      // instruction inlined in the case that it succeeds. We purposely
      // process the inlined body after inlining, because the inlining may
      // have exposed new inlining opportunities beyond those present in
      // the inlined function when processed independently.
      DEBUG(llvm::errs() << "Inlining @" << CalleeFunction->getName()
                         << " into @" << InnerAI.getFunction()->getName()
                         << "\n");

      // If we intend to inline a thick function, then we need to balance the
      // reference counts for correctness.
      if (IsThick && I != ApplyBlock->begin()) {
        // We need to find an appropriate location for our fix up code
        // We used to do this after inlining Without any modifications
        // This caused us to add a release in a wrong place:
        // It would release a value *before* retaining it!
        // It is really problematic to do this after inlining -
        // Finding a valid insertion point is tricky:
        // Inlining might add new basic blocks and/or remove the apply
        // We want to add the fix up *just before* where the current apply is!
        // Unfortunately, we *can't* add the fix up code here:
        // Inlining might fail for any reason -
        // If that occurred we'd need to undo our fix up code.
        // Instead, we split the current basic block -
        // Making sure we have a basic block that starts with our apply.
        SILBuilderWithScope B(I);
        ApplyBlock = splitBasicBlockAndBranch(B, &*I, nullptr, nullptr);
        I = ApplyBlock->begin();
      }

      // Decrement our iterator (carefully, to avoid going off the front) so it
      // is valid after inlining is done.  Inlining deletes the apply, and can
      // introduce multiple new basic blocks.
      if (I != ApplyBlock->begin())
        --I;
      else
        I = ApplyBlock->end();

      std::vector<Substitution> ApplySubs(InnerAI.getSubstitutions());

      if (PAI) {
        auto PAISubs = PAI->getSubstitutions();
        ApplySubs.insert(ApplySubs.end(), PAISubs.begin(), PAISubs.end());
      }

      SILOpenedArchetypesTracker OpenedArchetypesTracker(*F);
      F->getModule().registerDeleteNotificationHandler(
          &OpenedArchetypesTracker);
      // The callee only needs to know about opened archetypes used in
      // the substitution list.
      OpenedArchetypesTracker.registerUsedOpenedArchetypes(InnerAI.getInstruction());
      if (PAI) {
        OpenedArchetypesTracker.registerUsedOpenedArchetypes(PAI);
      }

      SILInliner Inliner(*F, *CalleeFunction,
                         SILInliner::InlineKind::MandatoryInline,
                         ApplySubs, OpenedArchetypesTracker);
      if (!Inliner.inlineFunction(InnerAI, FullArgs)) {
        I = InnerAI.getInstruction()->getIterator();
        continue;
      }

      // Inlining was successful. Remove the apply.
      InnerAI.getInstruction()->eraseFromParent();

      // Reestablish our iterator if it wrapped.
      if (I == ApplyBlock->end())
        I = ApplyBlock->begin();

      // Update the iterator when instructions are removed.
      DeleteInstructionsHandler DeletionHandler(I);

      // If the inlined apply was a thick function, then we need to balance the
      // reference counts for correctness.
      if (IsThick)
        fixupReferenceCounts(I, Loc, CalleeValue, CaptureArgs);

      // Now that the IR is correct, see if we can remove dead callee
      // computations (e.g. dead partial_apply closures).
      cleanupCalleeValue(CalleeValue, CaptureArgs, FullArgs);

      // Reposition iterators possibly invalidated by mutation.
      FI = SILFunction::iterator(ApplyBlock);
      E = ApplyBlock->end();
      assert(FI == SILFunction::iterator(I->getParent()) &&
             "Mismatch between the instruction and basic block");
      ++NumMandatoryInlines;
    }
  }

  // Keep track of full inlined functions so we don't waste time recursively
  // reprocessing them.
  FullyInlinedSet.insert(F);
  return true;
}