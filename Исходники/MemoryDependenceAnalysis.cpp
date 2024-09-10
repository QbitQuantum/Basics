/// getNonLocalPointerDepFromBB - Perform a dependency query based on
/// pointer/pointeesize starting at the end of StartBB.  Add any clobber/def
/// results to the results vector and keep track of which blocks are visited in
/// 'Visited'.
///
/// This has special behavior for the first block queries (when SkipFirstBlock
/// is true).  In this special case, it ignores the contents of the specified
/// block and starts returning dependence info for its predecessors.
///
/// This function returns false on success, or true to indicate that it could
/// not compute dependence information for some reason.  This should be treated
/// as a clobber dependence on the first instruction in the predecessor block.
bool MemoryDependenceAnalysis::
getNonLocalPointerDepFromBB(Value *Pointer, uint64_t PointeeSize,
                            bool isLoad, BasicBlock *StartBB,
                            SmallVectorImpl<NonLocalDepEntry> &Result,
                            DenseMap<BasicBlock*, Value*> &Visited,
                            bool SkipFirstBlock) {
  
  // Look up the cached info for Pointer.
  ValueIsLoadPair CacheKey(Pointer, isLoad);
  
  std::pair<BBSkipFirstBlockPair, NonLocalDepInfo> *CacheInfo =
    &NonLocalPointerDeps[CacheKey];
  NonLocalDepInfo *Cache = &CacheInfo->second;

  // If we have valid cached information for exactly the block we are
  // investigating, just return it with no recomputation.
  if (CacheInfo->first == BBSkipFirstBlockPair(StartBB, SkipFirstBlock)) {
    // We have a fully cached result for this query then we can just return the
    // cached results and populate the visited set.  However, we have to verify
    // that we don't already have conflicting results for these blocks.  Check
    // to ensure that if a block in the results set is in the visited set that
    // it was for the same pointer query.
    if (!Visited.empty()) {
      for (NonLocalDepInfo::iterator I = Cache->begin(), E = Cache->end();
           I != E; ++I) {
        DenseMap<BasicBlock*, Value*>::iterator VI = Visited.find(I->first);
        if (VI == Visited.end() || VI->second == Pointer) continue;
        
        // We have a pointer mismatch in a block.  Just return clobber, saying
        // that something was clobbered in this result.  We could also do a
        // non-fully cached query, but there is little point in doing this.
        return true;
      }
    }
    
    for (NonLocalDepInfo::iterator I = Cache->begin(), E = Cache->end();
         I != E; ++I) {
      Visited.insert(std::make_pair(I->first, Pointer));
      if (!I->second.isNonLocal())
        Result.push_back(*I);
    }
    ++NumCacheCompleteNonLocalPtr;
    return false;
  }
  
  // Otherwise, either this is a new block, a block with an invalid cache
  // pointer or one that we're about to invalidate by putting more info into it
  // than its valid cache info.  If empty, the result will be valid cache info,
  // otherwise it isn't.
  if (Cache->empty())
    CacheInfo->first = BBSkipFirstBlockPair(StartBB, SkipFirstBlock);
  else
    CacheInfo->first = BBSkipFirstBlockPair();
  
  SmallVector<BasicBlock*, 32> Worklist;
  Worklist.push_back(StartBB);
  
  // Keep track of the entries that we know are sorted.  Previously cached
  // entries will all be sorted.  The entries we add we only sort on demand (we
  // don't insert every element into its sorted position).  We know that we
  // won't get any reuse from currently inserted values, because we don't
  // revisit blocks after we insert info for them.
  unsigned NumSortedEntries = Cache->size();
  DEBUG(AssertSorted(*Cache));
  
  while (!Worklist.empty()) {
    BasicBlock *BB = Worklist.pop_back_val();
    
    // Skip the first block if we have it.
    if (!SkipFirstBlock) {
      // Analyze the dependency of *Pointer in FromBB.  See if we already have
      // been here.
      assert(Visited.count(BB) && "Should check 'visited' before adding to WL");

      // Get the dependency info for Pointer in BB.  If we have cached
      // information, we will use it, otherwise we compute it.
      DEBUG(AssertSorted(*Cache, NumSortedEntries));
      MemDepResult Dep = GetNonLocalInfoForBlock(Pointer, PointeeSize, isLoad,
                                                 BB, Cache, NumSortedEntries);
      
      // If we got a Def or Clobber, add this to the list of results.
      if (!Dep.isNonLocal()) {
        Result.push_back(NonLocalDepEntry(BB, Dep));
        continue;
      }
    }
    
    // If 'Pointer' is an instruction defined in this block, then we need to do
    // phi translation to change it into a value live in the predecessor block.
    // If phi translation fails, then we can't continue dependence analysis.
    Instruction *PtrInst = dyn_cast<Instruction>(Pointer);
    bool NeedsPHITranslation = PtrInst && PtrInst->getParent() == BB;
    
    // If no PHI translation is needed, just add all the predecessors of this
    // block to scan them as well.
    if (!NeedsPHITranslation) {
      SkipFirstBlock = false;
      for (BasicBlock **PI = PredCache->GetPreds(BB); *PI; ++PI) {
        // Verify that we haven't looked at this block yet.
        std::pair<DenseMap<BasicBlock*,Value*>::iterator, bool>
          InsertRes = Visited.insert(std::make_pair(*PI, Pointer));
        if (InsertRes.second) {
          // First time we've looked at *PI.
          Worklist.push_back(*PI);
          continue;
        }
        
        // If we have seen this block before, but it was with a different
        // pointer then we have a phi translation failure and we have to treat
        // this as a clobber.
        if (InsertRes.first->second != Pointer)
          goto PredTranslationFailure;
      }
      continue;
    }
    
    // If we do need to do phi translation, then there are a bunch of different
    // cases, because we have to find a Value* live in the predecessor block. We
    // know that PtrInst is defined in this block at least.
    
    // If this is directly a PHI node, just use the incoming values for each
    // pred as the phi translated version.
    if (PHINode *PtrPHI = dyn_cast<PHINode>(PtrInst)) {
      for (BasicBlock **PI = PredCache->GetPreds(BB); *PI; ++PI) {
        BasicBlock *Pred = *PI;
        Value *PredPtr = PtrPHI->getIncomingValueForBlock(Pred);
        
        // Check to see if we have already visited this pred block with another
        // pointer.  If so, we can't do this lookup.  This failure can occur
        // with PHI translation when a critical edge exists and the PHI node in
        // the successor translates to a pointer value different than the
        // pointer the block was first analyzed with.
        std::pair<DenseMap<BasicBlock*,Value*>::iterator, bool>
          InsertRes = Visited.insert(std::make_pair(Pred, PredPtr));

        if (!InsertRes.second) {
          // If the predecessor was visited with PredPtr, then we already did
          // the analysis and can ignore it.
          if (InsertRes.first->second == PredPtr)
            continue;
          
          // Otherwise, the block was previously analyzed with a different
          // pointer.  We can't represent the result of this case, so we just
          // treat this as a phi translation failure.
          goto PredTranslationFailure;
        }

        // We may have added values to the cache list before this PHI
        // translation.  If so, we haven't done anything to ensure that the
        // cache remains sorted.  Sort it now (if needed) so that recursive
        // invocations of getNonLocalPointerDepFromBB that could reuse the cache
        // value will only see properly sorted cache arrays.
        if (Cache && NumSortedEntries != Cache->size())
          std::sort(Cache->begin(), Cache->end());
        Cache = 0;
        
        // FIXME: it is entirely possible that PHI translating will end up with
        // the same value.  Consider PHI translating something like:
        // X = phi [x, bb1], [y, bb2].  PHI translating for bb1 doesn't *need*
        // to recurse here, pedantically speaking.
        
        // If we have a problem phi translating, fall through to the code below
        // to handle the failure condition.
        if (getNonLocalPointerDepFromBB(PredPtr, PointeeSize, isLoad, Pred,
                                        Result, Visited))
          goto PredTranslationFailure;
      }

      // Refresh the CacheInfo/Cache pointer so that it isn't invalidated.
      CacheInfo = &NonLocalPointerDeps[CacheKey];
      Cache = &CacheInfo->second;
      NumSortedEntries = Cache->size();
      
      // Since we did phi translation, the "Cache" set won't contain all of the
      // results for the query.  This is ok (we can still use it to accelerate
      // specific block queries) but we can't do the fastpath "return all
      // results from the set"  Clear out the indicator for this.
      CacheInfo->first = BBSkipFirstBlockPair();
      SkipFirstBlock = false;
      continue;
    }
    
    // TODO: BITCAST, GEP.
    
    //   cerr << "MEMDEP: Could not PHI translate: " << *Pointer;
    //   if (isa<BitCastInst>(PtrInst) || isa<GetElementPtrInst>(PtrInst))
    //     cerr << "OP:\t\t\t\t" << *PtrInst->getOperand(0);
  PredTranslationFailure:
    
    if (Cache == 0) {
      // Refresh the CacheInfo/Cache pointer if it got invalidated.
      CacheInfo = &NonLocalPointerDeps[CacheKey];
      Cache = &CacheInfo->second;
      NumSortedEntries = Cache->size();
    } else if (NumSortedEntries != Cache->size()) {
      std::sort(Cache->begin(), Cache->end());
      NumSortedEntries = Cache->size();
    }

    // Since we did phi translation, the "Cache" set won't contain all of the
    // results for the query.  This is ok (we can still use it to accelerate
    // specific block queries) but we can't do the fastpath "return all
    // results from the set"  Clear out the indicator for this.
    CacheInfo->first = BBSkipFirstBlockPair();
    
    // If *nothing* works, mark the pointer as being clobbered by the first
    // instruction in this block.
    //
    // If this is the magic first block, return this as a clobber of the whole
    // incoming value.  Since we can't phi translate to one of the predecessors,
    // we have to bail out.
    if (SkipFirstBlock)
      return true;
    
    for (NonLocalDepInfo::reverse_iterator I = Cache->rbegin(); ; ++I) {
      assert(I != Cache->rend() && "Didn't find current block??");
      if (I->first != BB)
        continue;
      
      assert(I->second.isNonLocal() &&
             "Should only be here with transparent block");
      I->second = MemDepResult::getClobber(BB->begin());
      ReverseNonLocalPtrDeps[BB->begin()].insert(CacheKey.getOpaqueValue());
      Result.push_back(*I);
      break;
    }
  }

  // Okay, we're done now.  If we added new values to the cache, re-sort it.
  switch (Cache->size()-NumSortedEntries) {
  case 0:
    // done, no new entries.
    break;
  case 2: {
    // Two new entries, insert the last one into place.
    NonLocalDepEntry Val = Cache->back();
    Cache->pop_back();
    NonLocalDepInfo::iterator Entry =
    std::upper_bound(Cache->begin(), Cache->end()-1, Val);
    Cache->insert(Entry, Val);
    // FALL THROUGH.
  }
  case 1:
    // One new entry, Just insert the new value at the appropriate position.
    if (Cache->size() != 1) {
      NonLocalDepEntry Val = Cache->back();
      Cache->pop_back();
      NonLocalDepInfo::iterator Entry =
        std::upper_bound(Cache->begin(), Cache->end(), Val);
      Cache->insert(Entry, Val);
    }
    break;
  default:
    // Added many values, do a full scale sort.
    std::sort(Cache->begin(), Cache->end());
  }
  DEBUG(AssertSorted(*Cache));
  return false;
}