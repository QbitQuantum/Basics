static void parsetypesynonym(void)
{
  Cell *head = pop();

  setchecktypevariables(COLLECT);
  push(template_match);
  for(; head->tag==APPLY; head=head->left)
  {
    if(head->right->tag != UNDEFINED && head->right->tag != FUNC) parseerror(9);
    push(maketypevariable(getfunction(head->right->value)->name));
    make(STRUCT);
  }
  if(head->tag != UNDEFINED && head->tag != FUNC) parseerror(10);
  makeconstant(FUNC, head->value);
  make(STRUCT);
  setchecktypevariables(CHECK);
  gettoken();
  parsetype(TYPEEXPR);
  makeinverse(TYPESYNONYM);
  if(!inserttypeexpr(getfunction(head->value)->name, pop())) parseerror(12);
  setchecktypevariables(NOCHECK);
}