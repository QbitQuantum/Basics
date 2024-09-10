bool UnrolledInstAnalyzer::visitPHINode(PHINode &PN) {
  // Run base visitor first. This way we can gather some useful for later
  // analysis information.
  if (Base::visitPHINode(PN))
    return true;

  // The loop induction PHI nodes are definitionally free.
  return PN.getParent() == L->getHeader();
}