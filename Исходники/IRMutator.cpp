Stmt IRMutator::mutate(Stmt s) {
    if (s.defined()) {
        s.accept(this);
    } else {
        stmt = Stmt();
    }
    expr = Expr();
    return stmt;
}