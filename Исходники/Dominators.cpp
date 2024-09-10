bool DominatorTree::dominates(const BasicBlockEdge &BBE, const Use &U) const {
  // Assert that we have a single edge. We could handle them by simply
  // returning false, but since isSingleEdge is linear on the number of
  // edges, the callers can normally handle them more efficiently.
  assert(BBE.isSingleEdge());

  Instruction *UserInst = cast<Instruction>(U.getUser());
  // A PHI in the end of the edge is dominated by it.
  PHINode *PN = dyn_cast<PHINode>(UserInst);
  if (PN && PN->getParent() == BBE.getEnd() &&
      PN->getIncomingBlock(U) == BBE.getStart())
    return true;

  // Otherwise use the edge-dominates-block query, which
  // handles the crazy critical edge cases properly.
  const BasicBlock *UseBB;
  if (PN)
    UseBB = PN->getIncomingBlock(U);
  else
    UseBB = UserInst->getParent();
  return dominates(BBE, UseBB);
}