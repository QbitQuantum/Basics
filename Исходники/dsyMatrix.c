SEXP dsyMatrix_as_matrix(SEXP from)
{
    int n = INTEGER(GET_SLOT(from, Matrix_DimSym))[0];
    SEXP val = PROTECT(allocMatrix(REALSXP, n, n));

    make_symmetric(Memcpy(REAL(val),
			  REAL(GET_SLOT(from, Matrix_xSym)), n * n),
		   from, n);
    setAttrib(val, R_DimNamesSymbol, GET_SLOT(from, Matrix_DimNamesSym));
    UNPROTECT(1);
    return val;
}