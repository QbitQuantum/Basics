bool
SemanticAnalysis::analyze(ParseTree *tree)
{
  for (size_t i = 0; i < tree->statements()->length(); i++) {
    Statement *stmt = tree->statements()->at(i);
    stmt->accept(this);

    if (!cc_.canContinueProcessing())
      return false;
  }

  return cc_.phasePassed();
}