static SEXP
createRSymbolObject(SEXP sname, DL_FUNC f, R_RegisteredNativeSymbol *symbol,
		    Rboolean withRegistrationInfo)
{
    SEXP tmp, klass, sym, names;
    int n = (symbol->type != R_ANY_SYM) ? 4 : 3;
    int numProtects = 0;

    PROTECT(sym = allocVector(VECSXP, n));    numProtects++;
    PROTECT(names = allocVector(STRSXP, n));    numProtects++;

    if(!sname || sname == R_NilValue) {
	PROTECT(sname = mkString(symbol->symbol.call->name));
	numProtects++;
    }

    SET_VECTOR_ELT(sym, 0, sname);
    SET_STRING_ELT(names, 0, mkChar("name"));

    SET_VECTOR_ELT(sym, 1,
		   withRegistrationInfo && symbol && symbol->symbol.c && symbol->dll
		   ? Rf_MakeRegisteredNativeSymbol(symbol)
		   : Rf_MakeNativeSymbolRef(f));
    SET_STRING_ELT(names, 1, mkChar("address"));
    if(symbol->dll)
	SET_VECTOR_ELT(sym, 2, Rf_MakeDLLInfo(symbol->dll));
    SET_STRING_ELT(names, 2, mkChar("dll"));


    PROTECT(klass = allocVector(STRSXP, (symbol->type != R_ANY_SYM ? 2 : 1)));
    numProtects++;
    SET_STRING_ELT(klass, length(klass)-1, mkChar("NativeSymbolInfo"));

    if(n > 3) {
	/* Add the registration information:
	   the number of arguments and the classname.
	*/
	int nargs = -1;
	char *className = "";
	switch(symbol->type) {
	case R_C_SYM:
	    nargs = symbol->symbol.c->numArgs;
	    className = "CRoutine";
	    break;
	case R_CALL_SYM:
	    nargs = symbol->symbol.call->numArgs;
	    className = "CallRoutine";
	    break;
	case R_FORTRAN_SYM:
	    nargs = symbol->symbol.fortran->numArgs;
	    className = "FortranRoutine";
	    break;
	case R_EXTERNAL_SYM:
	    nargs = symbol->symbol.external->numArgs;
	    className = "ExternalRoutine";
	    break;
	default:
	    /* Something unintended has happened if we get here. */
	    error(_("unimplemented type %d in 'createRSymbolObject'"),
		  symbol->type);
	    break;
	}
	SET_VECTOR_ELT(sym, 3, tmp = ScalarInteger(nargs));
	SET_STRING_ELT(klass, 0, mkChar(className));
	SET_STRING_ELT(names, 3, mkChar("numParameters"));
    }

    setAttrib(sym, R_ClassSymbol, klass);
    setAttrib(sym, R_NamesSymbol, names);

    UNPROTECT(numProtects);
    return(sym);
}