SEXP
createRVariantObject(VARIANT *var,  VARTYPE kind)
{
  const char *className;
  SEXP klass, ans, tmp;
  VARIANT *dupvar;  
  switch(kind) {
    case VT_DATE:
      className = "DateVARIANT";
      break;
    case VT_CY:
      className = "CurrencyVARIANT";
      break;

    default:
      className = "VARIANT";
  }

  PROTECT(klass = MAKE_CLASS(className));
  if(klass == NULL || klass == R_NilValue) {
     PROBLEM  "Can't locate S4 class definition %s", className
     ERROR;
  }
  
  dupvar = (VARIANT *) malloc(sizeof(VARIANT));
  VariantCopyInd(dupvar, var);
  
  PROTECT(ans = NEW(klass));
  PROTECT(tmp = R_MakeExternalPtr(dupvar, Rf_install(className), R_NilValue));
  R_RegisterCFinalizer(tmp, R_Variant_finalizer);
  SET_SLOT(ans, Rf_install("ref"), tmp);
  UNPROTECT(1);

  PROTECT(tmp = NEW_INTEGER(1));
  INTEGER(tmp)[0] = kind;
  SET_SLOT(ans, Rf_install("kind"), tmp);
  
  UNPROTECT(3);
  return(ans);
}