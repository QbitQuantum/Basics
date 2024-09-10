/// shouldEliminateUnconditionalBranch - Return true if this branch looks
/// attractive to eliminate.  We eliminate the branch if the destination basic
/// block has <= 5 instructions in it, not counting PHI nodes.  In practice,
/// since one of these is a terminator instruction, this means that we will add
/// up to 4 instructions to the new block.
///
/// We don't count PHI nodes in the count since they will be removed when the
/// contents of the block are copied over.
///
bool TailDup::shouldEliminateUnconditionalBranch(TerminatorInst *TI,
                                                 unsigned Threshold) {
  BranchInst *BI = dyn_cast<BranchInst>(TI);
  if (!BI || !BI->isUnconditional()) return false;  // Not an uncond branch!

  BasicBlock *Dest = BI->getSuccessor(0);
  if (Dest == BI->getParent()) return false;        // Do not loop infinitely!

  // Do not inline a block if we will just get another branch to the same block!
  TerminatorInst *DTI = Dest->getTerminator();
  if (BranchInst *DBI = dyn_cast<BranchInst>(DTI))
    if (DBI->isUnconditional() && DBI->getSuccessor(0) == Dest)
      return false;                                 // Do not loop infinitely!

  // FIXME: DemoteRegToStack cannot yet demote invoke instructions to the stack,
  // because doing so would require breaking critical edges.  This should be
  // fixed eventually.
  if (!DTI->use_empty())
    return false;

  // Do not bother with blocks with only a single predecessor: simplify
  // CFG will fold these two blocks together!
  pred_iterator PI = pred_begin(Dest), PE = pred_end(Dest);
  ++PI;
  if (PI == PE) return false;  // Exactly one predecessor!

  BasicBlock::iterator I = Dest->getFirstNonPHI();

  for (unsigned Size = 0; I != Dest->end(); ++I) {
    if (Size == Threshold) return false;  // The block is too large.
    
    // Don't tail duplicate call instructions.  They are very large compared to
    // other instructions.
    if (isa<CallInst>(I) || isa<InvokeInst>(I)) return false;

    // Also alloca and malloc.
    if (isa<AllocaInst>(I)) return false;

    // Some vector instructions can expand into a number of instructions.
    if (isa<ShuffleVectorInst>(I) || isa<ExtractElementInst>(I) ||
        isa<InsertElementInst>(I)) return false;
    
    // Only count instructions that are not debugger intrinsics.
    if (!isa<DbgInfoIntrinsic>(I)) ++Size;
  }

  // Do not tail duplicate a block that has thousands of successors into a block
  // with a single successor if the block has many other predecessors.  This can
  // cause an N^2 explosion in CFG edges (and PHI node entries), as seen in
  // cases that have a large number of indirect gotos.
  unsigned NumSuccs = DTI->getNumSuccessors();
  if (NumSuccs > 8) {
    unsigned TooMany = 128;
    if (NumSuccs >= TooMany) return false;
    TooMany = TooMany/NumSuccs;
    for (; PI != PE; ++PI)
      if (TooMany-- == 0) return false;
  }
  
  // If this unconditional branch is a fall-through, be careful about
  // tail duplicating it.  In particular, we don't want to taildup it if the
  // original block will still be there after taildup is completed: doing so
  // would eliminate the fall-through, requiring unconditional branches.
  Function::iterator DestI = Dest;
  if (&*--DestI == BI->getParent()) {
    // The uncond branch is a fall-through.  Tail duplication of the block is
    // will eliminate the fall-through-ness and end up cloning the terminator
    // at the end of the Dest block.  Since the original Dest block will
    // continue to exist, this means that one or the other will not be able to
    // fall through.  One typical example that this helps with is code like:
    // if (a)
    //   foo();
    // if (b)
    //   foo();
    // Cloning the 'if b' block into the end of the first foo block is messy.
    
    // The messy case is when the fall-through block falls through to other
    // blocks.  This is what we would be preventing if we cloned the block.
    DestI = Dest;
    if (++DestI != Dest->getParent()->end()) {
      BasicBlock *DestSucc = DestI;
      // If any of Dest's successors are fall-throughs, don't do this xform.
      for (succ_iterator SI = succ_begin(Dest), SE = succ_end(Dest);
           SI != SE; ++SI)
        if (*SI == DestSucc)
          return false;
    }
  }

  // Finally, check that we haven't redirected to this target block earlier;
  // there are cases where we loop forever if we don't check this (PR 2323).
  if (!CycleDetector.insert(Dest))
    return false;

  return true;
}