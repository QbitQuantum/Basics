bool
SemanticAnalysis::analyze()
{
    ParseTree *tree = tu_->tree();
    StatementList *statements = tree->statements();
    for (size_t i = 0; i < statements->length(); i++) {
        Statement *stmt = statements->at(i);
        if (stmt->isFunctionStatement())
            stmt->accept(this);
        if (!cc_.canContinueProcessing())
            return false;
    }
    return cc_.phasePassed();
}