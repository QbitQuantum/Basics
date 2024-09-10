void Stmt::printStmt()
{
  curToken=t.getToken();
  if(curToken == 32){
    cout<<t.getIdName();
    t.skipToken();
    curToken=t.getToken();
#ifdef ENABLE_DEBUG_PRINT
    cout<<" curToken-printStmt- Var "<<curToken<<endl;
#endif
    assign.printAssign();
  }
  else if(curToken==5) {
    cout<<" if ";
    t.skipToken();
    cond.printCondition();
    curToken=t.getToken();
    while(curToken != 3) {
      this->getIfInstanceStmt()->printIF();
      t.skipToken();
      curToken=t.getToken();
#ifdef ENABLE_DEBUG_PRINT
      cout<<" curToken-printStmt- if "<<curToken<<endl;
#endif
      if(curToken == 6){ cout<<" then "<<endl; t.skipToken(); }
      else if(curToken == 3) { cout<<" end "; }
      else if(curToken == 12) { cout<<" ; "<<endl; }
    }
  }
  else if(curToken==8) {
    cout<<" while ";
    t.skipToken();
    curToken=t.getToken();
    while(curToken != 3){
      this->getLoopInstanceStmt()->printLoop();
      t.skipToken();
      curToken=t.getToken();
#ifdef ENABLE_DEBUG_PRINT
      cout<<" curToken-printStmt- while "<<curToken<<endl;
#endif
      if(curToken == 9){ cout<<" loop "<<endl; t.skipToken(); }
      else if(curToken == 3) { cout<<" end "; }
      else if(curToken == 12) { cout<<" ; "<<endl; }
    }
  }
  else if(curToken==10) {
    cout<<" read ";
    t.skipToken();
    curToken=t.getToken();
    while(curToken != 12){
      in.printIN();
      t.skipToken();
      curToken=t.getToken();
#ifdef ENABLE_DEBUG_PRINT
      cout<<" curToken-printStmt- read "<<curToken<<endl;
#endif
      if(curToken==12) { cout<<"; "<<endl; }
      else if(curToken==13) { cout<<", "; }
      else if(curToken==14) { cout<<" = "; }
    }
  }
  else if(curToken==11) {
    cout<<" write ";
    t.skipToken();
    curToken=t.getToken();
#ifdef ENABLE_DEBUG_PRINT
    cout<<" curToken-printStmt- write "<<curToken<<endl;
#endif
    out.printOUT();
  }
}