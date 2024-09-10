/**
 * Unfolds the called macro by substituting its formal parameters with real
 * parameters
 *
 * @param called: called macro
 * @param realParams: real parameters
 * @return: unfolded formula
 */
ASTForm* unfoldFormula(PredLibEntry* called, ASTList* realParams) {
    IdentList* formalParams = called->formals;

    ASTForm* clonnedFormula = (called->ast)->clone();
    ASTForm* unfoldedFormula = clonnedFormula->unfoldMacro(formalParams, realParams);

    Flattener f_visitor;
    return static_cast<ASTForm*>(unfoldedFormula->accept(f_visitor));
}