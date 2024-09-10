/// \brief Recursively handle the condition leading to a loop
Value *SIAnnotateControlFlow::handleLoopCondition(
    Value *Cond, PHINode *Broken, llvm::Loop *L, BranchInst *Term,
    SmallVectorImpl<WeakTrackingVH> &LoopPhiConditions) {
  // Only search through PHI nodes which are inside the loop.  If we try this
  // with PHI nodes that are outside of the loop, we end up inserting new PHI
  // nodes outside of the loop which depend on values defined inside the loop.
  // This will break the module with
  // 'Instruction does not dominate all users!' errors.
  PHINode *Phi = nullptr;
  if ((Phi = dyn_cast<PHINode>(Cond)) && L->contains(Phi)) {
    BasicBlock *Parent = Phi->getParent();
    PHINode *NewPhi = PHINode::Create(Int64, 0, "loop.phi", &Parent->front());
    Value *Ret = NewPhi;

    // Handle all non-constant incoming values first
    for (unsigned i = 0, e = Phi->getNumIncomingValues(); i != e; ++i) {
      Value *Incoming = Phi->getIncomingValue(i);
      BasicBlock *From = Phi->getIncomingBlock(i);
      if (isa<ConstantInt>(Incoming)) {
        NewPhi->addIncoming(Broken, From);
        continue;
      }

      Phi->setIncomingValue(i, BoolFalse);
      Value *PhiArg = handleLoopCondition(Incoming, Broken, L,
                                          Term, LoopPhiConditions);
      NewPhi->addIncoming(PhiArg, From);
    }

    BasicBlock *IDom = DT->getNode(Parent)->getIDom()->getBlock();

    for (unsigned i = 0, e = Phi->getNumIncomingValues(); i != e; ++i) {
      Value *Incoming = Phi->getIncomingValue(i);
      if (Incoming != BoolTrue)
        continue;

      BasicBlock *From = Phi->getIncomingBlock(i);
      if (From == IDom) {
        // We're in the following situation:
        //   IDom/From
        //      |   \
        //      |   If-block
        //      |   /
        //     Parent
        // where we want to break out of the loop if the If-block is not taken.
        // Due to the depth-first traversal, there should be an end.cf
        // intrinsic in Parent, and we insert an else.break before it.
        //
        // Note that the end.cf need not be the first non-phi instruction
        // of parent, particularly when we're dealing with a multi-level
        // break, but it should occur within a group of intrinsic calls
        // at the beginning of the block.
        CallInst *OldEnd = dyn_cast<CallInst>(Parent->getFirstInsertionPt());
        while (OldEnd && OldEnd->getCalledFunction() != EndCf)
          OldEnd = dyn_cast<CallInst>(OldEnd->getNextNode());
        if (OldEnd && OldEnd->getCalledFunction() == EndCf) {
          Value *Args[] = { OldEnd->getArgOperand(0), NewPhi };
          Ret = CallInst::Create(ElseBreak, Args, "", OldEnd);
          continue;
        }
      }

      TerminatorInst *Insert = From->getTerminator();
      Value *PhiArg = CallInst::Create(Break, Broken, "", Insert);
      NewPhi->setIncomingValue(i, PhiArg);
    }

    LoopPhiConditions.push_back(WeakTrackingVH(Phi));
    return Ret;
  }

  if (Instruction *Inst = dyn_cast<Instruction>(Cond)) {
    BasicBlock *Parent = Inst->getParent();
    Instruction *Insert;
    if (L->contains(Inst)) {
      Insert = Parent->getTerminator();
    } else {
      Insert = L->getHeader()->getFirstNonPHIOrDbgOrLifetime();
    }

    Value *Args[] = { Cond, Broken };
    return CallInst::Create(IfBreak, Args, "", Insert);
  }

  // Insert IfBreak in the loop header TERM for constant COND other than true.
  if (isa<Constant>(Cond)) {
    Instruction *Insert = Cond == BoolTrue ?
      Term : L->getHeader()->getTerminator();

    Value *Args[] = { Cond, Broken };
    return CallInst::Create(IfBreak, Args, "", Insert);
  }

  llvm_unreachable("Unhandled loop condition!");
}