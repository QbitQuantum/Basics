static String *Swig_cmethod_call(String_or_char *name, ParmList *parms, String_or_char *self, String *explicit_qualifier, SwigType *director_type) {
  String *func, *nname;
  int i = 0;
  Parm *p = parms;
  SwigType *pt;
  int comma = 0;

  func = NewStringEmpty();
  if (!p)
    return func;

  if (!self)
    self = (char *) "(this)->";
  Append(func, self);

  if (SwigType_istemplate(name) && (strncmp(Char(name), "operator ", 9) == 0)) {
    /* fix for template + operators and compilers like gcc 3.3.5 */
    String *tprefix = SwigType_templateprefix(name);
    nname = tprefix;
  } else {
    nname = SwigType_namestr(name);
  }

  if (director_type) {
    const char *pname = "darg";
    String *rcaststr = SwigType_rcaststr(director_type, pname);
    Replaceall(func, "this", rcaststr);
    Delete(rcaststr);
  } else {
    pt = Getattr(p, k_type);

    /* If the method is invoked through a dereferenced pointer, we don't add any casts
       (needed for smart pointers).  Otherwise, we cast to the appropriate type */

    if (Strstr(func, "*this")) {
      String *pname = Swig_cparm_name(p, 0);
      Replaceall(func, "this", pname);
      Delete(pname);
    } else {
      String *pname = Swig_cparm_name(p, 0);
      String *rcaststr = SwigType_rcaststr(pt, pname);
      Replaceall(func, "this", rcaststr);
      Delete(rcaststr);
      Delete(pname);
    }

    /*
       SWIGTEMPLATEDESIMBUAGATOR is compiler dependent (swiglabels.swg),
       - SUN Studio 9 requires 'template', 
       - gcc-3.4 forbids the use of 'template' (correctly implementing the ISO C++ standard)
       the others don't seem to care,
     */
    if (SwigType_istemplate(name))
      Printf(func, "SWIGTEMPLATEDISAMBIGUATOR ");

    if (explicit_qualifier) {
      Printv(func, explicit_qualifier, "::", NIL);
    }
  }

  Printf(func, "%s(", nname);

  i++;
  p = nextSibling(p);
  while (p) {
    pt = Getattr(p, k_type);
    if ((SwigType_type(pt) != T_VOID)) {
      String *pname = Swig_cparm_name(p, i);
      String *rcaststr = SwigType_rcaststr(pt, pname);
      if (comma)
	Append(func, ",");
      Append(func, rcaststr);
      Delete(rcaststr);
      Delete(pname);
      comma = 1;
      i++;
    }
    p = nextSibling(p);
  }
  Append(func, ")");
  Delete(nname);
  return func;
}