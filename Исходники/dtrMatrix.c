SEXP dtrMatrix_as_matrix(SEXP from)
{
    int *Dim = INTEGER(GET_SLOT(from, Matrix_DimSym));
    int m = Dim[0], n = Dim[1];
    SEXP val = PROTECT(allocMatrix(REALSXP, m, n));
    make_d_matrix_triangular(Memcpy(REAL(val),
                                    REAL(GET_SLOT(from, Matrix_xSym)), m * n),
                             from);
    setAttrib(val, R_DimNamesSymbol, GET_SLOT(from, Matrix_DimNamesSym));
    UNPROTECT(1);
    return val;
}