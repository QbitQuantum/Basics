static bool
inlineCallsImpl(CallGraphSCC &SCC, CallGraph &CG,
                std::function<AssumptionCache &(Function &)> GetAssumptionCache,
                ProfileSummaryInfo *PSI, TargetLibraryInfo &TLI,
                bool InsertLifetime,
                function_ref<InlineCost(CallSite CS)> GetInlineCost,
                function_ref<AAResults &(Function &)> AARGetter,
                ImportedFunctionsInliningStatistics &ImportedFunctionsStats) {
  SmallPtrSet<Function *, 8> SCCFunctions;
  LLVM_DEBUG(dbgs() << "Inliner visiting SCC:");
  for (CallGraphNode *Node : SCC) {
    Function *F = Node->getFunction();
    if (F)
      SCCFunctions.insert(F);
    LLVM_DEBUG(dbgs() << " " << (F ? F->getName() : "INDIRECTNODE"));
  }

  // Scan through and identify all call sites ahead of time so that we only
  // inline call sites in the original functions, not call sites that result
  // from inlining other functions.
  SmallVector<std::pair<CallSite, int>, 16> CallSites;

  // When inlining a callee produces new call sites, we want to keep track of
  // the fact that they were inlined from the callee.  This allows us to avoid
  // infinite inlining in some obscure cases.  To represent this, we use an
  // index into the InlineHistory vector.
  SmallVector<std::pair<Function *, int>, 8> InlineHistory;

  for (CallGraphNode *Node : SCC) {
    Function *F = Node->getFunction();
    if (!F || F->isDeclaration())
      continue;

    OptimizationRemarkEmitter ORE(F);
    for (BasicBlock &BB : *F)
      for (Instruction &I : BB) {
        CallSite CS(cast<Value>(&I));
        // If this isn't a call, or it is a call to an intrinsic, it can
        // never be inlined.
        if (!CS || isa<IntrinsicInst>(I))
          continue;

        // If this is a direct call to an external function, we can never inline
        // it.  If it is an indirect call, inlining may resolve it to be a
        // direct call, so we keep it.
        if (Function *Callee = CS.getCalledFunction())
          if (Callee->isDeclaration()) {
            using namespace ore;

            ORE.emit([&]() {
              return OptimizationRemarkMissed(DEBUG_TYPE, "NoDefinition", &I)
                     << NV("Callee", Callee) << " will not be inlined into "
                     << NV("Caller", CS.getCaller())
                     << " because its definition is unavailable"
                     << setIsVerbose();
            });
            continue;
          }

        CallSites.push_back(std::make_pair(CS, -1));
      }
  }

  LLVM_DEBUG(dbgs() << ": " << CallSites.size() << " call sites.\n");

  // If there are no calls in this function, exit early.
  if (CallSites.empty())
    return false;

  // Now that we have all of the call sites, move the ones to functions in the
  // current SCC to the end of the list.
  unsigned FirstCallInSCC = CallSites.size();
  for (unsigned i = 0; i < FirstCallInSCC; ++i)
    if (Function *F = CallSites[i].first.getCalledFunction())
      if (SCCFunctions.count(F))
        std::swap(CallSites[i--], CallSites[--FirstCallInSCC]);

  InlinedArrayAllocasTy InlinedArrayAllocas;
  InlineFunctionInfo InlineInfo(&CG, &GetAssumptionCache, PSI);

  // Now that we have all of the call sites, loop over them and inline them if
  // it looks profitable to do so.
  bool Changed = false;
  bool LocalChange;
  do {
    LocalChange = false;
    // Iterate over the outer loop because inlining functions can cause indirect
    // calls to become direct calls.
    // CallSites may be modified inside so ranged for loop can not be used.
    for (unsigned CSi = 0; CSi != CallSites.size(); ++CSi) {
      CallSite CS = CallSites[CSi].first;

      Function *Caller = CS.getCaller();
      Function *Callee = CS.getCalledFunction();

      // We can only inline direct calls to non-declarations.
      if (!Callee || Callee->isDeclaration())
        continue;

      Instruction *Instr = CS.getInstruction();

      bool IsTriviallyDead = isInstructionTriviallyDead(Instr, &TLI);

      int InlineHistoryID;
      if (!IsTriviallyDead) {
        // If this call site was obtained by inlining another function, verify
        // that the include path for the function did not include the callee
        // itself.  If so, we'd be recursively inlining the same function,
        // which would provide the same callsites, which would cause us to
        // infinitely inline.
        InlineHistoryID = CallSites[CSi].second;
        if (InlineHistoryID != -1 &&
            InlineHistoryIncludes(Callee, InlineHistoryID, InlineHistory))
          continue;
      }

      // FIXME for new PM: because of the old PM we currently generate ORE and
      // in turn BFI on demand.  With the new PM, the ORE dependency should
      // just become a regular analysis dependency.
      OptimizationRemarkEmitter ORE(Caller);

      Optional<InlineCost> OIC = shouldInline(CS, GetInlineCost, ORE);
      // If the policy determines that we should inline this function,
      // delete the call instead.
      if (!OIC)
        continue;

      // If this call site is dead and it is to a readonly function, we should
      // just delete the call instead of trying to inline it, regardless of
      // size.  This happens because IPSCCP propagates the result out of the
      // call and then we're left with the dead call.
      if (IsTriviallyDead) {
        LLVM_DEBUG(dbgs() << "    -> Deleting dead call: " << *Instr << "\n");
        // Update the call graph by deleting the edge from Callee to Caller.
        CG[Caller]->removeCallEdgeFor(CS);
        Instr->eraseFromParent();
        ++NumCallsDeleted;
      } else {
        // Get DebugLoc to report. CS will be invalid after Inliner.
        DebugLoc DLoc = CS->getDebugLoc();
        BasicBlock *Block = CS.getParent();

        // Attempt to inline the function.
        using namespace ore;

        if (!InlineCallIfPossible(CS, InlineInfo, InlinedArrayAllocas,
                                  InlineHistoryID, InsertLifetime, AARGetter,
                                  ImportedFunctionsStats)) {
          ORE.emit([&]() {
            return OptimizationRemarkMissed(DEBUG_TYPE, "NotInlined", DLoc,
                                            Block)
                   << NV("Callee", Callee) << " will not be inlined into "
                   << NV("Caller", Caller);
          });
          continue;
        }
        ++NumInlined;

        ORE.emit([&]() {
          bool AlwaysInline = OIC->isAlways();
          StringRef RemarkName = AlwaysInline ? "AlwaysInline" : "Inlined";
          OptimizationRemark R(DEBUG_TYPE, RemarkName, DLoc, Block);
          R << NV("Callee", Callee) << " inlined into ";
          R << NV("Caller", Caller);
          if (AlwaysInline)
            R << " with cost=always";
          else {
            R << " with cost=" << NV("Cost", OIC->getCost());
            R << " (threshold=" << NV("Threshold", OIC->getThreshold());
            R << ")";
          }
          return R;
        });

        // If inlining this function gave us any new call sites, throw them
        // onto our worklist to process.  They are useful inline candidates.
        if (!InlineInfo.InlinedCalls.empty()) {
          // Create a new inline history entry for this, so that we remember
          // that these new callsites came about due to inlining Callee.
          int NewHistoryID = InlineHistory.size();
          InlineHistory.push_back(std::make_pair(Callee, InlineHistoryID));

          for (Value *Ptr : InlineInfo.InlinedCalls)
            CallSites.push_back(std::make_pair(CallSite(Ptr), NewHistoryID));
        }
      }

      // If we inlined or deleted the last possible call site to the function,
      // delete the function body now.
      if (Callee && Callee->use_empty() && Callee->hasLocalLinkage() &&
          // TODO: Can remove if in SCC now.
          !SCCFunctions.count(Callee) &&
          // The function may be apparently dead, but if there are indirect
          // callgraph references to the node, we cannot delete it yet, this
          // could invalidate the CGSCC iterator.
          CG[Callee]->getNumReferences() == 0) {
        LLVM_DEBUG(dbgs() << "    -> Deleting dead function: "
                          << Callee->getName() << "\n");
        CallGraphNode *CalleeNode = CG[Callee];

        // Remove any call graph edges from the callee to its callees.
        CalleeNode->removeAllCalledFunctions();

        // Removing the node for callee from the call graph and delete it.
        delete CG.removeFunctionFromModule(CalleeNode);
        ++NumDeleted;
      }

      // Remove this call site from the list.  If possible, use
      // swap/pop_back for efficiency, but do not use it if doing so would
      // move a call site to a function in this SCC before the
      // 'FirstCallInSCC' barrier.
      if (SCC.isSingular()) {
        CallSites[CSi] = CallSites.back();
        CallSites.pop_back();
      } else {
        CallSites.erase(CallSites.begin() + CSi);
      }
      --CSi;

      Changed = true;
      LocalChange = true;
    }
  } while (LocalChange);

  return Changed;
}