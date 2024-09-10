void
dopass_codegen(Program_ptr ast, SymTab * st)
{
    Codegen *codegen = new Codegen(stdout, st); //create the visitor
    ast->accept(codegen);                           //walk the tree with the visitor above
    delete codegen;
}