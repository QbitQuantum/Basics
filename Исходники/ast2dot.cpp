void dopass_ast2dot(Program_ptr ast) {
    Ast2dot* ast2dot = new Ast2dot(stdout); //create the visitor
    ast->accept(ast2dot); //walk the tree with the visitor above
    ast2dot->finish(); // finalize the printout
    delete ast2dot;
}