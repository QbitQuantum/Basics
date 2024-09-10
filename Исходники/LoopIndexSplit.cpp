/// processOneIterationLoop -- Eliminate loop if loop body is executed 
/// only once. For example,
/// for (i = 0; i < N; ++i) {
///   if ( i == X) {
///     ...
///   }
/// }
///
bool LoopIndexSplit::processOneIterationLoop() {
  SplitCondition = NULL;
  BasicBlock *Latch = L->getLoopLatch();
  BasicBlock *Header = L->getHeader();
  BranchInst *BR = dyn_cast<BranchInst>(Header->getTerminator());
  if (!BR) return false;
  if (!isa<BranchInst>(Latch->getTerminator())) return false;
  if (BR->isUnconditional()) return false;
  SplitCondition = dyn_cast<ICmpInst>(BR->getCondition());
  if (!SplitCondition) return false;
  if (SplitCondition == ExitCondition) return false;
  if (SplitCondition->getPredicate() != ICmpInst::ICMP_EQ) return false;
  if (BR->getOperand(1) != Latch) return false;
  if (!IVBasedValues.count(SplitCondition->getOperand(0))
      && !IVBasedValues.count(SplitCondition->getOperand(1)))
    return false;

  // If IV is used outside the loop then this loop traversal is required.
  // FIXME: Calculate and use last IV value. 
  if (isUsedOutsideLoop(IVIncrement, L))
    return false;

  // If BR operands are not IV or not loop invariants then skip this loop.
  Value *OPV = SplitCondition->getOperand(0);
  Value *SplitValue = SplitCondition->getOperand(1);
  if (!L->isLoopInvariant(SplitValue))
    std::swap(OPV, SplitValue);
  if (!L->isLoopInvariant(SplitValue))
    return false;
  Instruction *OPI = dyn_cast<Instruction>(OPV);
  if (!OPI) 
    return false;
  if (OPI->getParent() != Header || isUsedOutsideLoop(OPI, L))
    return false;
  Value *StartValue = IVStartValue;
  Value *ExitValue = IVExitValue;;

  if (OPV != IndVar) {
    // If BR operand is IV based then use this operand to calculate
    // effective conditions for loop body.
    BinaryOperator *BOPV = dyn_cast<BinaryOperator>(OPV);
    if (!BOPV) 
      return false;
    if (BOPV->getOpcode() != Instruction::Add) 
      return false;
    StartValue = BinaryOperator::CreateAdd(OPV, StartValue, "" , BR);
    ExitValue = BinaryOperator::CreateAdd(OPV, ExitValue, "" , BR);
  }

  if (!cleanBlock(Header))
    return false;

  if (!cleanBlock(Latch))
    return false;
    
  // If the merge point for BR is not loop latch then skip this loop.
  if (BR->getSuccessor(0) != Latch) {
    DominanceFrontier::iterator DF0 = DF->find(BR->getSuccessor(0));
    assert (DF0 != DF->end() && "Unable to find dominance frontier");
    if (!DF0->second.count(Latch))
      return false;
  }
  
  if (BR->getSuccessor(1) != Latch) {
    DominanceFrontier::iterator DF1 = DF->find(BR->getSuccessor(1));
    assert (DF1 != DF->end() && "Unable to find dominance frontier");
    if (!DF1->second.count(Latch))
      return false;
  }
    
  // Now, Current loop L contains compare instruction
  // that compares induction variable, IndVar, against loop invariant. And
  // entire (i.e. meaningful) loop body is dominated by this compare
  // instruction. In such case eliminate 
  // loop structure surrounding this loop body. For example,
  //     for (int i = start; i < end; ++i) {
  //         if ( i == somevalue) {
  //           loop_body
  //         }
  //     }
  // can be transformed into
  //     if (somevalue >= start && somevalue < end) {
  //        i = somevalue;
  //        loop_body
  //     }

  // Replace index variable with split value in loop body. Loop body is executed
  // only when index variable is equal to split value.
  IndVar->replaceAllUsesWith(SplitValue);

  // Replace split condition in header.
  // Transform 
  //      SplitCondition : icmp eq i32 IndVar, SplitValue
  // into
  //      c1 = icmp uge i32 SplitValue, StartValue
  //      c2 = icmp ult i32 SplitValue, ExitValue
  //      and i32 c1, c2 
  Instruction *C1 = new ICmpInst(BR, ExitCondition->isSigned() ? 
                                 ICmpInst::ICMP_SGE : ICmpInst::ICMP_UGE,
                                 SplitValue, StartValue, "lisplit");

  CmpInst::Predicate C2P  = ExitCondition->getPredicate();
  BranchInst *LatchBR = cast<BranchInst>(Latch->getTerminator());
  if (LatchBR->getOperand(1) != Header)
    C2P = CmpInst::getInversePredicate(C2P);
  Instruction *C2 = new ICmpInst(BR, C2P, SplitValue, ExitValue, "lisplit");
  Instruction *NSplitCond = BinaryOperator::CreateAnd(C1, C2, "lisplit", BR);

  SplitCondition->replaceAllUsesWith(NSplitCond);
  SplitCondition->eraseFromParent();

  // Remove Latch to Header edge.
  BasicBlock *LatchSucc = NULL;
  Header->removePredecessor(Latch);
  for (succ_iterator SI = succ_begin(Latch), E = succ_end(Latch);
       SI != E; ++SI) {
    if (Header != *SI)
      LatchSucc = *SI;
  }

  // Clean up latch block.
  Value *LatchBRCond = LatchBR->getCondition();
  LatchBR->setUnconditionalDest(LatchSucc);
  RecursivelyDeleteTriviallyDeadInstructions(LatchBRCond);
  
  LPM->deleteLoopFromQueue(L);

  // Update Dominator Info.
  // Only CFG change done is to remove Latch to Header edge. This
  // does not change dominator tree because Latch did not dominate
  // Header.
  if (DF) {
    DominanceFrontier::iterator HeaderDF = DF->find(Header);
    if (HeaderDF != DF->end()) 
      DF->removeFromFrontier(HeaderDF, Header);

    DominanceFrontier::iterator LatchDF = DF->find(Latch);
    if (LatchDF != DF->end()) 
      DF->removeFromFrontier(LatchDF, Header);
  }

  ++NumIndexSplitRemoved;
  return true;
}