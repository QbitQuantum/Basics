/// \brief Analyze a call site for potential inlining.
///
/// Returns true if inlining this call is viable, and false if it is not
/// viable. It computes the cost and adjusts the threshold based on numerous
/// factors and heuristics. If this method returns false but the computed cost
/// is below the computed threshold, then inlining was forcibly disabled by
/// some artifact of the routine.
bool CallAnalyzer::analyzeCall(CallSite CS) {
  ++NumCallsAnalyzed;

  // Track whether the post-inlining function would have more than one basic
  // block. A single basic block is often intended for inlining. Balloon the
  // threshold by 50% until we pass the single-BB phase.
  bool SingleBB = true;
  int SingleBBBonus = Threshold / 2;
  Threshold += SingleBBBonus;

  // Perform some tweaks to the cost and threshold based on the direct
  // callsite information.

  // We want to more aggressively inline vector-dense kernels, so up the
  // threshold, and we'll lower it if the % of vector instructions gets too
  // low.
  assert(NumInstructions == 0);
  assert(NumVectorInstructions == 0);
  FiftyPercentVectorBonus = Threshold;
  TenPercentVectorBonus = Threshold / 2;

  // Give out bonuses per argument, as the instructions setting them up will
  // be gone after inlining.
  for (unsigned I = 0, E = CS.arg_size(); I != E; ++I) {
    if (TD && CS.isByValArgument(I)) {
      // We approximate the number of loads and stores needed by dividing the
      // size of the byval type by the target's pointer size.
      PointerType *PTy = cast<PointerType>(CS.getArgument(I)->getType());
      unsigned TypeSize = TD->getTypeSizeInBits(PTy->getElementType());
      unsigned PointerSize = TD->getPointerSizeInBits();
      // Ceiling division.
      unsigned NumStores = (TypeSize + PointerSize - 1) / PointerSize;

      // If it generates more than 8 stores it is likely to be expanded as an
      // inline memcpy so we take that as an upper bound. Otherwise we assume
      // one load and one store per word copied.
      // FIXME: The maxStoresPerMemcpy setting from the target should be used
      // here instead of a magic number of 8, but it's not available via
      // DataLayout.
      NumStores = std::min(NumStores, 8U);

      Cost -= 2 * NumStores * InlineConstants::InstrCost;
    } else {
      // For non-byval arguments subtract off one instruction per call
      // argument.
      Cost -= InlineConstants::InstrCost;
    }
  }

  // If there is only one call of the function, and it has internal linkage,
  // the cost of inlining it drops dramatically.
  bool OnlyOneCallAndLocalLinkage = F.hasLocalLinkage() && F.hasOneUse() &&
    &F == CS.getCalledFunction();
  if (OnlyOneCallAndLocalLinkage)
    Cost += InlineConstants::LastCallToStaticBonus;

  // If the instruction after the call, or if the normal destination of the
  // invoke is an unreachable instruction, the function is noreturn. As such,
  // there is little point in inlining this unless there is literally zero
  // cost.
  Instruction *Instr = CS.getInstruction();
  if (InvokeInst *II = dyn_cast<InvokeInst>(Instr)) {
    if (isa<UnreachableInst>(II->getNormalDest()->begin()))
      Threshold = 1;
  } else if (isa<UnreachableInst>(++BasicBlock::iterator(Instr)))
    Threshold = 1;

  // If this function uses the coldcc calling convention, prefer not to inline
  // it.
  if (F.getCallingConv() == CallingConv::Cold)
    Cost += InlineConstants::ColdccPenalty;

  // Check if we're done. This can happen due to bonuses and penalties.
  if (Cost > Threshold)
    return false;

  if (F.empty())
    return true;

  Function *Caller = CS.getInstruction()->getParent()->getParent();
  // Check if the caller function is recursive itself.
  for (Value::use_iterator U = Caller->use_begin(), E = Caller->use_end();
       U != E; ++U) {
    CallSite Site(cast<Value>(*U));
    if (!Site)
      continue;
    Instruction *I = Site.getInstruction();
    if (I->getParent()->getParent() == Caller) {
      IsCallerRecursive = true;
      break;
    }
  }

  // Track whether we've seen a return instruction. The first return
  // instruction is free, as at least one will usually disappear in inlining.
  bool HasReturn = false;

  // Populate our simplified values by mapping from function arguments to call
  // arguments with known important simplifications.
  CallSite::arg_iterator CAI = CS.arg_begin();
  for (Function::arg_iterator FAI = F.arg_begin(), FAE = F.arg_end();
       FAI != FAE; ++FAI, ++CAI) {
    assert(CAI != CS.arg_end());
    if (Constant *C = dyn_cast<Constant>(CAI))
      SimplifiedValues[FAI] = C;

    Value *PtrArg = *CAI;
    if (ConstantInt *C = stripAndComputeInBoundsConstantOffsets(PtrArg)) {
      ConstantOffsetPtrs[FAI] = std::make_pair(PtrArg, C->getValue());

      // We can SROA any pointer arguments derived from alloca instructions.
      if (isa<AllocaInst>(PtrArg)) {
        SROAArgValues[FAI] = PtrArg;
        SROAArgCosts[PtrArg] = 0;
      }
    }
  }
  NumConstantArgs = SimplifiedValues.size();
  NumConstantOffsetPtrArgs = ConstantOffsetPtrs.size();
  NumAllocaArgs = SROAArgValues.size();

  // The worklist of live basic blocks in the callee *after* inlining. We avoid
  // adding basic blocks of the callee which can be proven to be dead for this
  // particular call site in order to get more accurate cost estimates. This
  // requires a somewhat heavyweight iteration pattern: we need to walk the
  // basic blocks in a breadth-first order as we insert live successors. To
  // accomplish this, prioritizing for small iterations because we exit after
  // crossing our threshold, we use a small-size optimized SetVector.
  typedef SetVector<BasicBlock *, SmallVector<BasicBlock *, 16>,
                                  SmallPtrSet<BasicBlock *, 16> > BBSetVector;
  BBSetVector BBWorklist;
  BBWorklist.insert(&F.getEntryBlock());
  // Note that we *must not* cache the size, this loop grows the worklist.
  for (unsigned Idx = 0; Idx != BBWorklist.size(); ++Idx) {
    // Bail out the moment we cross the threshold. This means we'll under-count
    // the cost, but only when undercounting doesn't matter.
    if (Cost > (Threshold + VectorBonus))
      break;

    BasicBlock *BB = BBWorklist[Idx];
    if (BB->empty())
      continue;

    // Handle the terminator cost here where we can track returns and other
    // function-wide constructs.
    TerminatorInst *TI = BB->getTerminator();

    // We never want to inline functions that contain an indirectbr.  This is
    // incorrect because all the blockaddress's (in static global initializers
    // for example) would be referring to the original function, and this
    // indirect jump would jump from the inlined copy of the function into the 
    // original function which is extremely undefined behavior.
    // FIXME: This logic isn't really right; we can safely inline functions
    // with indirectbr's as long as no other function or global references the
    // blockaddress of a block within the current function.  And as a QOI issue,
    // if someone is using a blockaddress without an indirectbr, and that
    // reference somehow ends up in another function or global, we probably
    // don't want to inline this function.
    if (isa<IndirectBrInst>(TI))
      return false;

    if (!HasReturn && isa<ReturnInst>(TI))
      HasReturn = true;
    else
      Cost += InlineConstants::InstrCost;

    // Analyze the cost of this block. If we blow through the threshold, this
    // returns false, and we can bail on out.
    if (!analyzeBlock(BB)) {
      if (IsRecursiveCall || ExposesReturnsTwice || HasDynamicAlloca)
        return false;

      // If the caller is a recursive function then we don't want to inline
      // functions which allocate a lot of stack space because it would increase
      // the caller stack usage dramatically.
      if (IsCallerRecursive &&
          AllocatedSize > InlineConstants::TotalAllocaSizeRecursiveCaller)
        return false;

      break;
    }

    // Add in the live successors by first checking whether we have terminator
    // that may be simplified based on the values simplified by this call.
    if (BranchInst *BI = dyn_cast<BranchInst>(TI)) {
      if (BI->isConditional()) {
        Value *Cond = BI->getCondition();
        if (ConstantInt *SimpleCond
              = dyn_cast_or_null<ConstantInt>(SimplifiedValues.lookup(Cond))) {
          BBWorklist.insert(BI->getSuccessor(SimpleCond->isZero() ? 1 : 0));
          continue;
        }
      }
    } else if (SwitchInst *SI = dyn_cast<SwitchInst>(TI)) {
      Value *Cond = SI->getCondition();
      if (ConstantInt *SimpleCond
            = dyn_cast_or_null<ConstantInt>(SimplifiedValues.lookup(Cond))) {
        BBWorklist.insert(SI->findCaseValue(SimpleCond).getCaseSuccessor());
        continue;
      }
    }

    // If we're unable to select a particular successor, just count all of
    // them.
    for (unsigned TIdx = 0, TSize = TI->getNumSuccessors(); TIdx != TSize;
         ++TIdx)
      BBWorklist.insert(TI->getSuccessor(TIdx));

    // If we had any successors at this point, than post-inlining is likely to
    // have them as well. Note that we assume any basic blocks which existed
    // due to branches or switches which folded above will also fold after
    // inlining.
    if (SingleBB && TI->getNumSuccessors() > 1) {
      // Take off the bonus we applied to the threshold.
      Threshold -= SingleBBBonus;
      SingleBB = false;
    }
  }

  // If this is a noduplicate call, we can still inline as long as 
  // inlining this would cause the removal of the caller (so the instruction
  // is not actually duplicated, just moved).
  if (!OnlyOneCallAndLocalLinkage && ContainsNoDuplicateCall)
    return false;

  Threshold += VectorBonus;

  return Cost < Threshold;
}