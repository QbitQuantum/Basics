void
ConsumedResultToEpilogueRetainMatcher::
findMatchingRetains(SILBasicBlock *BB) {
  // Iterate over the instructions post-order and find retains associated with
  // return value.
  SILValue RV = SILValue();
  for (auto II = BB->rbegin(), IE = BB->rend(); II != IE; ++II) {
    if (ReturnInst *RI = dyn_cast<ReturnInst>(&*II)) {
      RV = RI->getOperand();
      break;
    }
  }

  // Somehow, we managed not to find a return value.
  if (!RV)
    return;

  // OK. we've found the return value, now iterate on the CFG to find all the
  // post-dominating retains.
  //
  // The ConsumedArgToEpilogueReleaseMatcher finds the final releases
  // in the following way. 
  //
  // 1. If an instruction, which is not releaseinst nor releasevalue, that
  // could decrement reference count is found. bail out.
  //
  // 2. If a release is found and the release that can not be mapped to any
  // @owned argument. bail as this release may well be the final release of
  // an @owned argument, but somehow rc-identity fails to prove that.
  //
  // 3. A release that is mapped to an argument which already has a release
  // that overlaps with this release. This release for sure is not the final
  // release.
  constexpr unsigned WorkListMaxSize = 4;

  llvm::DenseSet<SILBasicBlock *> RetainFrees;
  llvm::SmallVector<BasicBlockRetainValue, 4> WorkList;
  llvm::DenseSet<SILBasicBlock *> HandledBBs;
  WorkList.push_back(std::make_pair(BB, RV));
  HandledBBs.insert(BB);
  while (!WorkList.empty()) {
    // Too many blocks ?.
    if (WorkList.size() > WorkListMaxSize) {
      EpilogueRetainInsts.clear();
      return;
    }

    // Try to find a retain %value in this basic block.
    auto R = WorkList.pop_back_val();
    RetainKindValue Kind = findMatchingRetainsInBasicBlock(R.first, R.second);

    // We've found a retain on this path.
    if (Kind.first == FindRetainKind::Found) { 
      EpilogueRetainInsts.push_back(Kind.second);
      continue;
    }

    // There is a MayDecrement instruction.
    if (Kind.first == FindRetainKind::Blocked) {
      EpilogueRetainInsts.clear();
      return;
    }

    // There is a self-recursion. Use the apply instruction as the retain.
    if (Kind.first == FindRetainKind::Recursion) {
      EpilogueRetainInsts.push_back(Kind.second);
      continue;
    }
  
    // Did not find a retain in this block, try to go to its predecessors.
    if (Kind.first == FindRetainKind::None) {
      // We can not find a retain in a block with no predecessors.
      if (R.first->getPreds().begin() == R.first->getPreds().end()) {
        EpilogueRetainInsts.clear();
        return;
      }

      // This block does not have a retain.
      RetainFrees.insert(R.first);

      // If this is a SILArgument of current basic block, we can split it up to
      // values in the predecessors.
      SILArgument *SA = dyn_cast<SILArgument>(R.second);
      if (SA && SA->getParent() != R.first)
        SA = nullptr;

      for (auto X : R.first->getPreds()) {
        if (HandledBBs.find(X) != HandledBBs.end())
          continue;
        // Try to use the predecessor edge-value.
        if (SA && SA->getIncomingValue(X)) {
          WorkList.push_back(std::make_pair(X, SA->getIncomingValue(X)));
        }
        else 
          WorkList.push_back(std::make_pair(X, R.second));
   
        HandledBBs.insert(X);
      }
    }
  }

  // Lastly, check whether all the successor blocks are retain-free.
  if (!isTransitiveSuccessorsRetainFree(RetainFrees))
    EpilogueRetainInsts.clear();

  // At this point, we've either failed to find any epilogue retains or
  // all the post-dominating epilogue retains.
}