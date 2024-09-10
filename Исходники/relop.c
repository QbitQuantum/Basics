SEXP attribute_hidden do_relop_dflt(SEXP call, SEXP op, SEXP x, SEXP y)
{
    SEXP klass = R_NilValue, dims, tsp=R_NilValue, xnames, ynames;
    int nx, ny, xarray, yarray, xts, yts;
    Rboolean mismatch = FALSE, iS;
    PROTECT_INDEX xpi, ypi;

    PROTECT_WITH_INDEX(x, &xpi);
    PROTECT_WITH_INDEX(y, &ypi);
    nx = length(x);
    ny = length(y);

    /* pre-test to handle the most common case quickly.
       Used to skip warning too ....
     */
    if (ATTRIB(x) == R_NilValue && ATTRIB(y) == R_NilValue &&
	TYPEOF(x) == REALSXP && TYPEOF(y) == REALSXP &&
	LENGTH(x) > 0 && LENGTH(y) > 0) {
	SEXP ans = real_relop((RELOP_TYPE) PRIMVAL(op), x, y);
	if (nx > 0 && ny > 0)
	    mismatch = ((nx > ny) ? nx % ny : ny % nx) != 0;
	if (mismatch) {
	    PROTECT(ans);
	    warningcall(call, _("longer object length is not a multiple of shorter object length"));
	    UNPROTECT(1);
	}
	UNPROTECT(2);
	return ans;
    }

    /* That symbols and calls were allowed was undocumented prior to
       R 2.5.0.  We deparse them as deparse() would, minus attributes */
    if ((iS = isSymbol(x)) || TYPEOF(x) == LANGSXP) {
	SEXP tmp = allocVector(STRSXP, 1);
	PROTECT(tmp);
	SET_STRING_ELT(tmp, 0, (iS) ? PRINTNAME(x) :
		       STRING_ELT(deparse1(x, 0, DEFAULTDEPARSE), 0));
	REPROTECT(x = tmp, xpi);
	UNPROTECT(1);
    }
    if ((iS = isSymbol(y)) || TYPEOF(y) == LANGSXP) {
	SEXP tmp = allocVector(STRSXP, 1);
	PROTECT(tmp);
	SET_STRING_ELT(tmp, 0, (iS) ? PRINTNAME(y) :
		       STRING_ELT(deparse1(y, 0, DEFAULTDEPARSE), 0));
	REPROTECT(y = tmp, ypi);
	UNPROTECT(1);
    }

    if (!isVector(x) || !isVector(y)) {
	if (isNull(x) || isNull(y)) {
	    UNPROTECT(2);
	    return allocVector(LGLSXP,0);
	}
	errorcall(call,
		  _("comparison (%d) is possible only for atomic and list types"),
		  PRIMVAL(op));
    }

    if (TYPEOF(x) == EXPRSXP || TYPEOF(y) == EXPRSXP)
	errorcall(call, _("comparison is not allowed for expressions"));

    /* ELSE :  x and y are both atomic or list */

    if (LENGTH(x) <= 0 || LENGTH(y) <= 0) {
	UNPROTECT(2);
	return allocVector(LGLSXP,0);
    }

    mismatch = FALSE;
    xarray = isArray(x);
    yarray = isArray(y);
    xts = isTs(x);
    yts = isTs(y);
    if (nx > 0 && ny > 0)
	mismatch = ((nx > ny) ? nx % ny : ny % nx) != 0;

    if (xarray || yarray) {
	if (xarray && yarray) {
	    if (!conformable(x, y))
		errorcall(call, _("non-conformable arrays"));
	    PROTECT(dims = getAttrib(x, R_DimSymbol));
	}
	else if (xarray) {
	    PROTECT(dims = getAttrib(x, R_DimSymbol));
	}
	else /*(yarray)*/ {
	    PROTECT(dims = getAttrib(y, R_DimSymbol));
	}
	PROTECT(xnames = getAttrib(x, R_DimNamesSymbol));
	PROTECT(ynames = getAttrib(y, R_DimNamesSymbol));
    }
    else {
	PROTECT(dims = R_NilValue);
	PROTECT(xnames = getAttrib(x, R_NamesSymbol));
	PROTECT(ynames = getAttrib(y, R_NamesSymbol));
    }
    if (xts || yts) {
	if (xts && yts) {
	    if (!tsConform(x, y))
		errorcall(call, _("non-conformable time series"));
	    PROTECT(tsp = getAttrib(x, R_TspSymbol));
	    PROTECT(klass = getAttrib(x, R_ClassSymbol));
	}
	else if (xts) {
	    if (length(x) < length(y))
		ErrorMessage(call, ERROR_TSVEC_MISMATCH);
	    PROTECT(tsp = getAttrib(x, R_TspSymbol));
	    PROTECT(klass = getAttrib(x, R_ClassSymbol));
	}
	else /*(yts)*/ {
	    if (length(y) < length(x))
		ErrorMessage(call, ERROR_TSVEC_MISMATCH);
	    PROTECT(tsp = getAttrib(y, R_TspSymbol));
	    PROTECT(klass = getAttrib(y, R_ClassSymbol));
	}
    }
    if (mismatch)
	warningcall(call, _("longer object length is not a multiple of shorter object length"));

    if (isString(x) || isString(y)) {
	REPROTECT(x = coerceVector(x, STRSXP), xpi);
	REPROTECT(y = coerceVector(y, STRSXP), ypi);
	x = string_relop((RELOP_TYPE) PRIMVAL(op), x, y);
    }
    else if (isComplex(x) || isComplex(y)) {
	REPROTECT(x = coerceVector(x, CPLXSXP), xpi);
	REPROTECT(y = coerceVector(y, CPLXSXP), ypi);
	x = complex_relop((RELOP_TYPE) PRIMVAL(op), x, y, call);
    }
    else if (isReal(x) || isReal(y)) {
	REPROTECT(x = coerceVector(x, REALSXP), xpi);
	REPROTECT(y = coerceVector(y, REALSXP), ypi);
	x = real_relop((RELOP_TYPE) PRIMVAL(op), x, y);
    }
    else if (isInteger(x) || isInteger(y)) {
	REPROTECT(x = coerceVector(x, INTSXP), xpi);
	REPROTECT(y = coerceVector(y, INTSXP), ypi);
	x = integer_relop((RELOP_TYPE) PRIMVAL(op), x, y);
    }
    else if (isLogical(x) || isLogical(y)) {
	REPROTECT(x = coerceVector(x, LGLSXP), xpi);
	REPROTECT(y = coerceVector(y, LGLSXP), ypi);
	x = integer_relop((RELOP_TYPE) PRIMVAL(op), x, y);
    }
    else if (TYPEOF(x) == RAWSXP || TYPEOF(y) == RAWSXP) {
	REPROTECT(x = coerceVector(x, RAWSXP), xpi);
	REPROTECT(y = coerceVector(y, RAWSXP), ypi);
	x = raw_relop((RELOP_TYPE) PRIMVAL(op), x, y);
    } else errorcall(call, _("comparison of these types is not implemented"));


    PROTECT(x);
    if (dims != R_NilValue) {
	setAttrib(x, R_DimSymbol, dims);
	if (xnames != R_NilValue)
	    setAttrib(x, R_DimNamesSymbol, xnames);
	else if (ynames != R_NilValue)
	    setAttrib(x, R_DimNamesSymbol, ynames);
    }
    else {
	if (length(x) == length(xnames))
	    setAttrib(x, R_NamesSymbol, xnames);
	else if (length(x) == length(ynames))
	    setAttrib(x, R_NamesSymbol, ynames);
    }
    if (xts || yts) {
	setAttrib(x, R_TspSymbol, tsp);
	setAttrib(x, R_ClassSymbol, klass);
	UNPROTECT(2);
    }

    UNPROTECT(6);
    return x;
}