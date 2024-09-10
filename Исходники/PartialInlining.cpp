bool PartialInlinerImpl::shouldPartialInline(
    CallSite CS, FunctionCloner &Cloner, BlockFrequency WeightedOutliningRcost,
    OptimizationRemarkEmitter &ORE) {

  using namespace ore;
  if (SkipCostAnalysis)
    return true;

  Instruction *Call = CS.getInstruction();
  Function *Callee = CS.getCalledFunction();
  assert(Callee == Cloner.ClonedFunc);

  Function *Caller = CS.getCaller();
  auto &CalleeTTI = (*GetTTI)(*Callee);
  InlineCost IC = getInlineCost(CS, getInlineParams(), CalleeTTI,
                                *GetAssumptionCache, GetBFI, PSI, &ORE);

  if (IC.isAlways()) {
    ORE.emit(OptimizationRemarkAnalysis(DEBUG_TYPE, "AlwaysInline", Call)
             << NV("Callee", Cloner.OrigFunc)
             << " should always be fully inlined, not partially");
    return false;
  }

  if (IC.isNever()) {
    ORE.emit(OptimizationRemarkMissed(DEBUG_TYPE, "NeverInline", Call)
             << NV("Callee", Cloner.OrigFunc) << " not partially inlined into "
             << NV("Caller", Caller)
             << " because it should never be inlined (cost=never)");
    return false;
  }

  if (!IC) {
    ORE.emit(OptimizationRemarkAnalysis(DEBUG_TYPE, "TooCostly", Call)
             << NV("Callee", Cloner.OrigFunc) << " not partially inlined into "
             << NV("Caller", Caller) << " because too costly to inline (cost="
             << NV("Cost", IC.getCost()) << ", threshold="
             << NV("Threshold", IC.getCostDelta() + IC.getCost()) << ")");
    return false;
  }
  const DataLayout &DL = Caller->getParent()->getDataLayout();

  // The savings of eliminating the call:
  int NonWeightedSavings = getCallsiteCost(CS, DL);
  BlockFrequency NormWeightedSavings(NonWeightedSavings);

  // Weighted saving is smaller than weighted cost, return false
  if (NormWeightedSavings < WeightedOutliningRcost) {
    ORE.emit(
        OptimizationRemarkAnalysis(DEBUG_TYPE, "OutliningCallcostTooHigh", Call)
        << NV("Callee", Cloner.OrigFunc) << " not partially inlined into "
        << NV("Caller", Caller) << " runtime overhead (overhead="
        << NV("Overhead", (unsigned)WeightedOutliningRcost.getFrequency())
        << ", savings="
        << NV("Savings", (unsigned)NormWeightedSavings.getFrequency()) << ")"
        << " of making the outlined call is too high");

    return false;
  }

  ORE.emit(OptimizationRemarkAnalysis(DEBUG_TYPE, "CanBePartiallyInlined", Call)
           << NV("Callee", Cloner.OrigFunc) << " can be partially inlined into "
           << NV("Caller", Caller) << " with cost=" << NV("Cost", IC.getCost())
           << " (threshold="
           << NV("Threshold", IC.getCostDelta() + IC.getCost()) << ")");
  return true;
}