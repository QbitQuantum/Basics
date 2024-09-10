// RewriteLoopBodyWithConditionConstant - We know either that the value LIC has
// the value specified by Val in the specified loop, or we know it does NOT have
// that value.  Rewrite any uses of LIC or of properties correlated to it.
void LoopUnswitch::RewriteLoopBodyWithConditionConstant(Loop *L, Value *LIC,
                                                        Constant *Val,
                                                        bool IsEqual) {
  assert(!isa<Constant>(LIC) && "Why are we unswitching on a constant?");
  
  // FIXME: Support correlated properties, like:
  //  for (...)
  //    if (li1 < li2)
  //      ...
  //    if (li1 > li2)
  //      ...
  
  // FOLD boolean conditions (X|LIC), (X&LIC).  Fold conditional branches,
  // selects, switches.
  std::vector<User*> Users(LIC->use_begin(), LIC->use_end());
  std::vector<Instruction*> Worklist;
  LLVMContext &Context = Val->getContext();


  // If we know that LIC == Val, or that LIC == NotVal, just replace uses of LIC
  // in the loop with the appropriate one directly.
  if (IsEqual || (isa<ConstantInt>(Val) &&
      Val->getType()->isIntegerTy(1))) {
    Value *Replacement;
    if (IsEqual)
      Replacement = Val;
    else
      Replacement = ConstantInt::get(Type::getInt1Ty(Val->getContext()), 
                                     !cast<ConstantInt>(Val)->getZExtValue());
    
    for (unsigned i = 0, e = Users.size(); i != e; ++i)
      if (Instruction *U = cast<Instruction>(Users[i])) {
        if (!L->contains(U))
          continue;
        U->replaceUsesOfWith(LIC, Replacement);
        Worklist.push_back(U);
      }
    SimplifyCode(Worklist, L);
    return;
  }
  
  // Otherwise, we don't know the precise value of LIC, but we do know that it
  // is certainly NOT "Val".  As such, simplify any uses in the loop that we
  // can.  This case occurs when we unswitch switch statements.
  for (unsigned i = 0, e = Users.size(); i != e; ++i) {
    Instruction *U = cast<Instruction>(Users[i]);
    if (!L->contains(U))
      continue;

    Worklist.push_back(U);

    // TODO: We could do other simplifications, for example, turning 
    // 'icmp eq LIC, Val' -> false.

    // If we know that LIC is not Val, use this info to simplify code.
    SwitchInst *SI = dyn_cast<SwitchInst>(U);
    if (SI == 0 || !isa<ConstantInt>(Val)) continue;
    
    unsigned DeadCase = SI->findCaseValue(cast<ConstantInt>(Val));
    if (DeadCase == 0) continue;  // Default case is live for multiple values.
    
    // Found a dead case value.  Don't remove PHI nodes in the 
    // successor if they become single-entry, those PHI nodes may
    // be in the Users list.
        
    // FIXME: This is a hack.  We need to keep the successor around
    // and hooked up so as to preserve the loop structure, because
    // trying to update it is complicated.  So instead we preserve the
    // loop structure and put the block on a dead code path.
    BasicBlock *Switch = SI->getParent();
    SplitEdge(Switch, SI->getSuccessor(DeadCase), this);
    // Compute the successors instead of relying on the return value
    // of SplitEdge, since it may have split the switch successor
    // after PHI nodes.
    BasicBlock *NewSISucc = SI->getSuccessor(DeadCase);
    BasicBlock *OldSISucc = *succ_begin(NewSISucc);
    // Create an "unreachable" destination.
    BasicBlock *Abort = BasicBlock::Create(Context, "us-unreachable",
                                           Switch->getParent(),
                                           OldSISucc);
    new UnreachableInst(Context, Abort);
    // Force the new case destination to branch to the "unreachable"
    // block while maintaining a (dead) CFG edge to the old block.
    NewSISucc->getTerminator()->eraseFromParent();
    BranchInst::Create(Abort, OldSISucc,
                       ConstantInt::getTrue(Context), NewSISucc);
    // Release the PHI operands for this edge.
    for (BasicBlock::iterator II = NewSISucc->begin();
         PHINode *PN = dyn_cast<PHINode>(II); ++II)
      PN->setIncomingValue(PN->getBasicBlockIndex(Switch),
                           UndefValue::get(PN->getType()));
    // Tell the domtree about the new block. We don't fully update the
    // domtree here -- instead we force it to do a full recomputation
    // after the pass is complete -- but we do need to inform it of
    // new blocks.
    if (DT)
      DT->addNewBlock(Abort, NewSISucc);
  }
  
  SimplifyCode(Worklist, L);
}