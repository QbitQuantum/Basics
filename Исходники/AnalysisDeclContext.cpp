/// Add each synthetic statement in the CFG to the parent map, using the
/// source statement's parent.
static void addParentsForSyntheticStmts(const CFG *TheCFG, ParentMap &PM) {
  if (!TheCFG)
    return;

  for (CFG::synthetic_stmt_iterator I = TheCFG->synthetic_stmt_begin(),
                                    E = TheCFG->synthetic_stmt_end();
       I != E; ++I) {
    PM.setParent(I->first, PM.getParent(I->second));
  }
}