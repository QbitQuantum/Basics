/// getEdgeValue - This method attempts to infer more complex 
bool LazyValueInfoCache::getEdgeValue(Value *Val, BasicBlock *BBFrom,
                                      BasicBlock *BBTo, LVILatticeVal &Result) {
  // If already a constant, there is nothing to compute.
  if (Constant *VC = dyn_cast<Constant>(Val)) {
    Result = LVILatticeVal::get(VC);
    return true;
  }
  
  // TODO: Handle more complex conditionals.  If (v == 0 || v2 < 1) is false, we
  // know that v != 0.
  if (BranchInst *BI = dyn_cast<BranchInst>(BBFrom->getTerminator())) {
    // If this is a conditional branch and only one successor goes to BBTo, then
    // we maybe able to infer something from the condition. 
    if (BI->isConditional() &&
        BI->getSuccessor(0) != BI->getSuccessor(1)) {
      bool isTrueDest = BI->getSuccessor(0) == BBTo;
      assert(BI->getSuccessor(!isTrueDest) == BBTo &&
             "BBTo isn't a successor of BBFrom");
      
      // If V is the condition of the branch itself, then we know exactly what
      // it is.
      if (BI->getCondition() == Val) {
        Result = LVILatticeVal::get(ConstantInt::get(
                              Type::getInt1Ty(Val->getContext()), isTrueDest));
        return true;
      }
      
      // If the condition of the branch is an equality comparison, we may be
      // able to infer the value.
      ICmpInst *ICI = dyn_cast<ICmpInst>(BI->getCondition());
      if (ICI && ICI->getOperand(0) == Val &&
          isa<Constant>(ICI->getOperand(1))) {
        if (ICI->isEquality()) {
          // We know that V has the RHS constant if this is a true SETEQ or
          // false SETNE. 
          if (isTrueDest == (ICI->getPredicate() == ICmpInst::ICMP_EQ))
            Result = LVILatticeVal::get(cast<Constant>(ICI->getOperand(1)));
          else
            Result = LVILatticeVal::getNot(cast<Constant>(ICI->getOperand(1)));
          return true;
        }

        if (ConstantInt *CI = dyn_cast<ConstantInt>(ICI->getOperand(1))) {
          // Calculate the range of values that would satisfy the comparison.
          ConstantRange CmpRange(CI->getValue(), CI->getValue()+1);
          ConstantRange TrueValues =
            ConstantRange::makeICmpRegion(ICI->getPredicate(), CmpRange);

          // If we're interested in the false dest, invert the condition.
          if (!isTrueDest) TrueValues = TrueValues.inverse();
          
          // Figure out the possible values of the query BEFORE this branch.  
          if (!hasBlockValue(Val, BBFrom)) {
            BlockValueStack.push(std::make_pair(BBFrom, Val));
            return false;
          }
          
          LVILatticeVal InBlock = getBlockValue(Val, BBFrom);
          if (!InBlock.isConstantRange()) {
            Result = LVILatticeVal::getRange(TrueValues);
            return true;
          }

          // Find all potential values that satisfy both the input and output
          // conditions.
          ConstantRange PossibleValues =
            TrueValues.intersectWith(InBlock.getConstantRange());

          Result = LVILatticeVal::getRange(PossibleValues);
          return true;
        }
      }
    }
  }

  // If the edge was formed by a switch on the value, then we may know exactly
  // what it is.
  if (SwitchInst *SI = dyn_cast<SwitchInst>(BBFrom->getTerminator())) {
    if (SI->getCondition() == Val) {
      // We don't know anything in the default case.
      if (SI->getDefaultDest() == BBTo) {
        Result.markOverdefined();
        return true;
      }
      
      // We only know something if there is exactly one value that goes from
      // BBFrom to BBTo.
      unsigned NumEdges = 0;
      ConstantInt *EdgeVal = 0;
      for (unsigned i = 1, e = SI->getNumSuccessors(); i != e; ++i) {
        if (SI->getSuccessor(i) != BBTo) continue;
        if (NumEdges++) break;
        EdgeVal = SI->getCaseValue(i);
      }
      assert(EdgeVal && "Missing successor?");
      if (NumEdges == 1) {
        Result = LVILatticeVal::get(EdgeVal);
        return true;
      }
    }
  }
  
  // Otherwise see if the value is known in the block.
  if (hasBlockValue(Val, BBFrom)) {
    Result = getBlockValue(Val, BBFrom);
    return true;
  }
  BlockValueStack.push(std::make_pair(BBFrom, Val));
  return false;
}