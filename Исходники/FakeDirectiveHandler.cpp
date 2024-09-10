bool FakeDirectiveHandler::VisitCompoundStmt(CompoundStmt *S) {

  if (WaitingHeader) {

    CompilerInstance &CI = FullDirectives->GetCI(S->getLocStart());

    if (IsChild(S, WaitingHeader)) {
      return true;
    }

    FullDirectives->Push(WaitingDirective, WaitingHeader, S, CI);
    
    WaitingDirective = NULL;
    WaitingHeader = NULL;
    
    return true;
  
  } else {

    PragmaDirectiveMap::iterator it;
    
    it = Directives->find(S->getLocStart().getRawEncoding());
  
    if (it != Directives->end()) {
    
      WaitingHeader = S;
      WaitingDirective = it->second;
    
    }
    
    return true;
    
  }

}