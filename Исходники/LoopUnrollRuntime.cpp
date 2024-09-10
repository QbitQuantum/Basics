/// Connect the unrolling epilog code to the original loop.
/// The unrolling epilog code contains code to execute the
/// 'extra' iterations if the run-time trip count modulo the
/// unroll count is non-zero.
///
/// This function performs the following:
/// - Update PHI nodes at the unrolling loop exit and epilog loop exit
/// - Create PHI nodes at the unrolling loop exit to combine
///   values that exit the unrolling loop code and jump around it.
/// - Update PHI operands in the epilog loop by the new PHI nodes
/// - Branch around the epilog loop if extra iters (ModVal) is zero.
///
static void ConnectEpilog(Loop *L, Value *ModVal, BasicBlock *NewExit,
                          BasicBlock *Exit, BasicBlock *PreHeader,
                          BasicBlock *EpilogPreHeader, BasicBlock *NewPreHeader,
                          ValueToValueMapTy &VMap, DominatorTree *DT,
                          LoopInfo *LI, bool PreserveLCSSA)  {
  BasicBlock *Latch = L->getLoopLatch();
  assert(Latch && "Loop must have a latch");
  BasicBlock *EpilogLatch = cast<BasicBlock>(VMap[Latch]);

  // Loop structure should be the following:
  //
  // PreHeader
  // NewPreHeader
  //   Header
  //   ...
  //   Latch
  // NewExit (PN)
  // EpilogPreHeader
  //   EpilogHeader
  //   ...
  //   EpilogLatch
  // Exit (EpilogPN)

  // Update PHI nodes at NewExit and Exit.
  for (Instruction &BBI : *NewExit) {
    PHINode *PN = dyn_cast<PHINode>(&BBI);
    // Exit when we passed all PHI nodes.
    if (!PN)
      break;
    // PN should be used in another PHI located in Exit block as
    // Exit was split by SplitBlockPredecessors into Exit and NewExit
    // Basicaly it should look like:
    // NewExit:
    //   PN = PHI [I, Latch]
    // ...
    // Exit:
    //   EpilogPN = PHI [PN, EpilogPreHeader]
    //
    // There is EpilogPreHeader incoming block instead of NewExit as
    // NewExit was spilt 1 more time to get EpilogPreHeader.
    assert(PN->hasOneUse() && "The phi should have 1 use");
    PHINode *EpilogPN = cast<PHINode> (PN->use_begin()->getUser());
    assert(EpilogPN->getParent() == Exit && "EpilogPN should be in Exit block");

    // Add incoming PreHeader from branch around the Loop
    PN->addIncoming(UndefValue::get(PN->getType()), PreHeader);

    Value *V = PN->getIncomingValueForBlock(Latch);
    Instruction *I = dyn_cast<Instruction>(V);
    if (I && L->contains(I))
      // If value comes from an instruction in the loop add VMap value.
      V = VMap.lookup(I);
    // For the instruction out of the loop, constant or undefined value
    // insert value itself.
    EpilogPN->addIncoming(V, EpilogLatch);

    assert(EpilogPN->getBasicBlockIndex(EpilogPreHeader) >= 0 &&
          "EpilogPN should have EpilogPreHeader incoming block");
    // Change EpilogPreHeader incoming block to NewExit.
    EpilogPN->setIncomingBlock(EpilogPN->getBasicBlockIndex(EpilogPreHeader),
                               NewExit);
    // Now PHIs should look like:
    // NewExit:
    //   PN = PHI [I, Latch], [undef, PreHeader]
    // ...
    // Exit:
    //   EpilogPN = PHI [PN, NewExit], [VMap[I], EpilogLatch]
  }

  // Create PHI nodes at NewExit (from the unrolling loop Latch and PreHeader).
  // Update corresponding PHI nodes in epilog loop.
  for (BasicBlock *Succ : successors(Latch)) {
    // Skip this as we already updated phis in exit blocks.
    if (!L->contains(Succ))
      continue;
    for (Instruction &BBI : *Succ) {
      PHINode *PN = dyn_cast<PHINode>(&BBI);
      // Exit when we passed all PHI nodes.
      if (!PN)
        break;
      // Add new PHI nodes to the loop exit block and update epilog
      // PHIs with the new PHI values.
      PHINode *NewPN = PHINode::Create(PN->getType(), 2, PN->getName() + ".unr",
                                       NewExit->getFirstNonPHI());
      // Adding a value to the new PHI node from the unrolling loop preheader.
      NewPN->addIncoming(PN->getIncomingValueForBlock(NewPreHeader), PreHeader);
      // Adding a value to the new PHI node from the unrolling loop latch.
      NewPN->addIncoming(PN->getIncomingValueForBlock(Latch), Latch);

      // Update the existing PHI node operand with the value from the new PHI
      // node.  Corresponding instruction in epilog loop should be PHI.
      PHINode *VPN = cast<PHINode>(VMap[&BBI]);
      VPN->setIncomingValue(VPN->getBasicBlockIndex(EpilogPreHeader), NewPN);
    }
  }

  Instruction *InsertPt = NewExit->getTerminator();
  IRBuilder<> B(InsertPt);
  Value *BrLoopExit = B.CreateIsNotNull(ModVal, "lcmp.mod");
  assert(Exit && "Loop must have a single exit block only");
  // Split the epilogue exit to maintain loop canonicalization guarantees
  SmallVector<BasicBlock*, 4> Preds(predecessors(Exit));
  SplitBlockPredecessors(Exit, Preds, ".epilog-lcssa", DT, LI,
                         PreserveLCSSA);
  // Add the branch to the exit block (around the unrolling loop)
  B.CreateCondBr(BrLoopExit, EpilogPreHeader, Exit);
  InsertPt->eraseFromParent();
  if (DT)
    DT->changeImmediateDominator(Exit, NewExit);

  // Split the main loop exit to maintain canonicalization guarantees.
  SmallVector<BasicBlock*, 4> NewExitPreds{Latch};
  SplitBlockPredecessors(NewExit, NewExitPreds, ".loopexit", DT, LI,
                         PreserveLCSSA);
}