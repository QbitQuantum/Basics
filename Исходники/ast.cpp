bool CAstStatAssign::TypeCheck(CToken *t, string *msg) const
{
  CAstDesignator *id = GetLHS();
  CAstExpression *e = GetRHS();
  
  if (!id->TypeCheck(t, msg)) return false;
  if (!e->TypeCheck(t, msg)) return false;

  if (!id->GetType()->Match(e->GetType())) {
    if (t != NULL) *t = e->GetToken();
    if (msg != NULL) *msg = "assignment type mismatch.";
    return false;
  }

  return true;
}