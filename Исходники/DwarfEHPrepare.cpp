/// MoveExceptionValueCalls - Ensure that eh.exception is only ever called from
/// landing pads by replacing calls outside of landing pads with direct use of
/// a register holding the appropriate value; this requires adding calls inside
/// all landing pads to initialize the register.  Also, move eh.exception calls
/// inside landing pads to the start of the landing pad (optional, but may make
/// things simpler for later passes).
bool DwarfEHPrepare::MoveExceptionValueCalls() {
  // If the eh.exception intrinsic is not declared in the module then there is
  // nothing to do.  Speed up compilation by checking for this common case.
  if (!ExceptionValueIntrinsic &&
      !F->getParent()->getFunction(Intrinsic::getName(Intrinsic::eh_exception)))
    return false;

  bool Changed = false;

  // Move calls to eh.exception that are inside a landing pad to the start of
  // the landing pad.
  for (BBSet::const_iterator LI = LandingPads.begin(), LE = LandingPads.end();
       LI != LE; ++LI) {
    BasicBlock *LP = *LI;
    for (BasicBlock::iterator II = LP->getFirstNonPHIOrDbg(), IE = LP->end();
         II != IE;)
      if (EHExceptionInst *EI = dyn_cast<EHExceptionInst>(II++)) {
        // Found a call to eh.exception.
        if (!EI->use_empty()) {
          // If there is already a call to eh.exception at the start of the
          // landing pad, then get hold of it; otherwise create such a call.
          Value *CallAtStart = CreateExceptionValueCall(LP);

          // If the call was at the start of a landing pad then leave it alone.
          if (EI == CallAtStart)
            continue;
          EI->replaceAllUsesWith(CallAtStart);
        }
        EI->eraseFromParent();
        ++NumExceptionValuesMoved;
        Changed = true;
      }
  }

  // Look for calls to eh.exception that are not in a landing pad.  If one is
  // found, then a register that holds the exception value will be created in
  // each landing pad, and the SSAUpdater will be used to compute the values
  // returned by eh.exception calls outside of landing pads.
  SSAUpdater SSA;

  // Remember where we found the eh.exception call, to avoid rescanning earlier
  // basic blocks which we already know contain no eh.exception calls.
  bool FoundCallOutsideLandingPad = false;
  Function::iterator BB = F->begin();
  for (Function::iterator BE = F->end(); BB != BE; ++BB) {
    // Skip over landing pads.
    if (LandingPads.count(BB))
      continue;

    for (BasicBlock::iterator II = BB->getFirstNonPHIOrDbg(), IE = BB->end();
         II != IE; ++II)
      if (isa<EHExceptionInst>(II)) {
        SSA.Initialize(II->getType(), II->getName());
        FoundCallOutsideLandingPad = true;
        break;
      }

    if (FoundCallOutsideLandingPad)
      break;
  }

  // If all calls to eh.exception are in landing pads then we are done.
  if (!FoundCallOutsideLandingPad)
    return Changed;

  // Add a call to eh.exception at the start of each landing pad, and tell the
  // SSAUpdater that this is the value produced by the landing pad.
  for (BBSet::iterator LI = LandingPads.begin(), LE = LandingPads.end();
       LI != LE; ++LI)
    SSA.AddAvailableValue(*LI, CreateExceptionValueCall(*LI));

  // Now turn all calls to eh.exception that are not in a landing pad into a use
  // of the appropriate register.
  for (Function::iterator BE = F->end(); BB != BE; ++BB) {
    // Skip over landing pads.
    if (LandingPads.count(BB))
      continue;

    for (BasicBlock::iterator II = BB->getFirstNonPHIOrDbg(), IE = BB->end();
         II != IE;)
      if (EHExceptionInst *EI = dyn_cast<EHExceptionInst>(II++)) {
        // Found a call to eh.exception, replace it with the value from any
        // upstream landing pad(s).
        EI->replaceAllUsesWith(SSA.GetValueAtEndOfBlock(BB));
        EI->eraseFromParent();
        ++NumExceptionValuesMoved;
      }
  }

  return true;
}