bool GlobalMerge::doMerge(SmallVectorImpl<GlobalVariable*> &Globals,
                          Module &M, bool isConst, unsigned AddrSpace) const {
  auto &DL = M.getDataLayout();
  // FIXME: Find better heuristics
  std::stable_sort(Globals.begin(), Globals.end(),
                   [&DL](const GlobalVariable *GV1, const GlobalVariable *GV2) {
                     return DL.getTypeAllocSize(GV1->getValueType()) <
                            DL.getTypeAllocSize(GV2->getValueType());
                   });

  // If we want to just blindly group all globals together, do so.
  if (!GlobalMergeGroupByUse) {
    BitVector AllGlobals(Globals.size());
    AllGlobals.set();
    return doMerge(Globals, AllGlobals, M, isConst, AddrSpace);
  }

  // If we want to be smarter, look at all uses of each global, to try to
  // discover all sets of globals used together, and how many times each of
  // these sets occurred.
  //
  // Keep this reasonably efficient, by having an append-only list of all sets
  // discovered so far (UsedGlobalSet), and mapping each "together-ness" unit of
  // code (currently, a Function) to the set of globals seen so far that are
  // used together in that unit (GlobalUsesByFunction).
  //
  // When we look at the Nth global, we know that any new set is either:
  // - the singleton set {N}, containing this global only, or
  // - the union of {N} and a previously-discovered set, containing some
  //   combination of the previous N-1 globals.
  // Using that knowledge, when looking at the Nth global, we can keep:
  // - a reference to the singleton set {N} (CurGVOnlySetIdx)
  // - a list mapping each previous set to its union with {N} (EncounteredUGS),
  //   if it actually occurs.

  // We keep track of the sets of globals used together "close enough".
  struct UsedGlobalSet {
    BitVector Globals;
    unsigned UsageCount = 1;

    UsedGlobalSet(size_t Size) : Globals(Size) {}
  };

  // Each set is unique in UsedGlobalSets.
  std::vector<UsedGlobalSet> UsedGlobalSets;

  // Avoid repeating the create-global-set pattern.
  auto CreateGlobalSet = [&]() -> UsedGlobalSet & {
    UsedGlobalSets.emplace_back(Globals.size());
    return UsedGlobalSets.back();
  };

  // The first set is the empty set.
  CreateGlobalSet().UsageCount = 0;

  // We define "close enough" to be "in the same function".
  // FIXME: Grouping uses by function is way too aggressive, so we should have
  // a better metric for distance between uses.
  // The obvious alternative would be to group by BasicBlock, but that's in
  // turn too conservative..
  // Anything in between wouldn't be trivial to compute, so just stick with
  // per-function grouping.

  // The value type is an index into UsedGlobalSets.
  // The default (0) conveniently points to the empty set.
  DenseMap<Function *, size_t /*UsedGlobalSetIdx*/> GlobalUsesByFunction;

  // Now, look at each merge-eligible global in turn.

  // Keep track of the sets we already encountered to which we added the
  // current global.
  // Each element matches the same-index element in UsedGlobalSets.
  // This lets us efficiently tell whether a set has already been expanded to
  // include the current global.
  std::vector<size_t> EncounteredUGS;

  for (size_t GI = 0, GE = Globals.size(); GI != GE; ++GI) {
    GlobalVariable *GV = Globals[GI];

    // Reset the encountered sets for this global...
    std::fill(EncounteredUGS.begin(), EncounteredUGS.end(), 0);
    // ...and grow it in case we created new sets for the previous global.
    EncounteredUGS.resize(UsedGlobalSets.size());

    // We might need to create a set that only consists of the current global.
    // Keep track of its index into UsedGlobalSets.
    size_t CurGVOnlySetIdx = 0;

    // For each global, look at all its Uses.
    for (auto &U : GV->uses()) {
      // This Use might be a ConstantExpr.  We're interested in Instruction
      // users, so look through ConstantExpr...
      Use *UI, *UE;
      if (ConstantExpr *CE = dyn_cast<ConstantExpr>(U.getUser())) {
        if (CE->use_empty())
          continue;
        UI = &*CE->use_begin();
        UE = nullptr;
      } else if (isa<Instruction>(U.getUser())) {
        UI = &U;
        UE = UI->getNext();
      } else {
        continue;
      }

      // ...to iterate on all the instruction users of the global.
      // Note that we iterate on Uses and not on Users to be able to getNext().
      for (; UI != UE; UI = UI->getNext()) {
        Instruction *I = dyn_cast<Instruction>(UI->getUser());
        if (!I)
          continue;

        Function *ParentFn = I->getParent()->getParent();

        // If we're only optimizing for size, ignore non-minsize functions.
        if (OnlyOptimizeForSize && !ParentFn->optForMinSize())
          continue;

        size_t UGSIdx = GlobalUsesByFunction[ParentFn];

        // If this is the first global the basic block uses, map it to the set
        // consisting of this global only.
        if (!UGSIdx) {
          // If that set doesn't exist yet, create it.
          if (!CurGVOnlySetIdx) {
            CurGVOnlySetIdx = UsedGlobalSets.size();
            CreateGlobalSet().Globals.set(GI);
          } else {
            ++UsedGlobalSets[CurGVOnlySetIdx].UsageCount;
          }

          GlobalUsesByFunction[ParentFn] = CurGVOnlySetIdx;
          continue;
        }

        // If we already encountered this BB, just increment the counter.
        if (UsedGlobalSets[UGSIdx].Globals.test(GI)) {
          ++UsedGlobalSets[UGSIdx].UsageCount;
          continue;
        }

        // If not, the previous set wasn't actually used in this function.
        --UsedGlobalSets[UGSIdx].UsageCount;

        // If we already expanded the previous set to include this global, just
        // reuse that expanded set.
        if (size_t ExpandedIdx = EncounteredUGS[UGSIdx]) {
          ++UsedGlobalSets[ExpandedIdx].UsageCount;
          GlobalUsesByFunction[ParentFn] = ExpandedIdx;
          continue;
        }

        // If not, create a new set consisting of the union of the previous set
        // and this global.  Mark it as encountered, so we can reuse it later.
        GlobalUsesByFunction[ParentFn] = EncounteredUGS[UGSIdx] =
            UsedGlobalSets.size();

        UsedGlobalSet &NewUGS = CreateGlobalSet();
        NewUGS.Globals.set(GI);
        NewUGS.Globals |= UsedGlobalSets[UGSIdx].Globals;
      }
    }
  }

  // Now we found a bunch of sets of globals used together.  We accumulated
  // the number of times we encountered the sets (i.e., the number of blocks
  // that use that exact set of globals).
  //
  // Multiply that by the size of the set to give us a crude profitability
  // metric.
  std::stable_sort(UsedGlobalSets.begin(), UsedGlobalSets.end(),
            [](const UsedGlobalSet &UGS1, const UsedGlobalSet &UGS2) {
              return UGS1.Globals.count() * UGS1.UsageCount <
                     UGS2.Globals.count() * UGS2.UsageCount;
            });

  // We can choose to merge all globals together, but ignore globals never used
  // with another global.  This catches the obviously non-profitable cases of
  // having a single global, but is aggressive enough for any other case.
  if (GlobalMergeIgnoreSingleUse) {
    BitVector AllGlobals(Globals.size());
    for (size_t i = 0, e = UsedGlobalSets.size(); i != e; ++i) {
      const UsedGlobalSet &UGS = UsedGlobalSets[e - i - 1];
      if (UGS.UsageCount == 0)
        continue;
      if (UGS.Globals.count() > 1)
        AllGlobals |= UGS.Globals;
    }
    return doMerge(Globals, AllGlobals, M, isConst, AddrSpace);
  }

  // Starting from the sets with the best (=biggest) profitability, find a
  // good combination.
  // The ideal (and expensive) solution can only be found by trying all
  // combinations, looking for the one with the best profitability.
  // Don't be smart about it, and just pick the first compatible combination,
  // starting with the sets with the best profitability.
  BitVector PickedGlobals(Globals.size());
  bool Changed = false;

  for (size_t i = 0, e = UsedGlobalSets.size(); i != e; ++i) {
    const UsedGlobalSet &UGS = UsedGlobalSets[e - i - 1];
    if (UGS.UsageCount == 0)
      continue;
    if (PickedGlobals.anyCommon(UGS.Globals))
      continue;
    PickedGlobals |= UGS.Globals;
    // If the set only contains one global, there's no point in merging.
    // Ignore the global for inclusion in other sets though, so keep it in
    // PickedGlobals.
    if (UGS.Globals.count() < 2)
      continue;
    Changed |= doMerge(Globals, UGS.Globals, M, isConst, AddrSpace);
  }

  return Changed;
}