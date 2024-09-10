Stmt IRRewriter::rewrite(Stmt s) {
  if (s.defined()) {
    s.accept(this);
    Stmt spilledStmts = getSpilledStmts();
    if (spilledStmts.defined()) {
      stmt = Block::make(spilledStmts, stmt);
    }
    s = stmt;
  }
  else {
    s = Stmt();
  }
  expr = Expr();
  stmt = Stmt();
  func = Func();
  return s;
}