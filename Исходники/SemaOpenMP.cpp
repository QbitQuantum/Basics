bool DSAStackTy::isOpenMPLocal(VarDecl *D, StackTy::reverse_iterator Iter) {
  if (Stack.size() > 2) {
    reverse_iterator I = Iter, E = Stack.rend() - 1;
    Scope *TopScope = 0;
    while (I != E &&
           I->Directive != OMPD_parallel) {
      ++I;
    }
    if (I == E) return false;
    TopScope = I->CurScope ? I->CurScope->getParent() : 0;
    Scope *CurScope = getCurScope();
    while (CurScope != TopScope && !CurScope->isDeclScope(D)) {
      CurScope = CurScope->getParent();
    }
    return CurScope != TopScope;
  }
  return false;
}