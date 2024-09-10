/* Returns the function type, t, constructed from the parameters, parms */
SwigType *SwigType_add_function(SwigType *t, ParmList *parms) {
  String *pstr;
  Parm *p;

  Insert(t, 0, ").");
  pstr = NewString("f(");
  for (p = parms; p; p = nextSibling(p)) {
    if (p != parms)
      Putc(',', pstr);
    Append(pstr, Getattr(p, "type"));
  }
  Insert(t, 0, pstr);
  Delete(pstr);
  return t;
}