SEXP dtCMatrix_sparse_solve(SEXP a, SEXP b)
{
    SEXP ans = PROTECT(NEW_OBJECT(MAKE_CLASS("dgCMatrix")));
    CSP A = AS_CSP(a), B = AS_CSP(b);
    int *xp = INTEGER(ALLOC_SLOT(ans, Matrix_pSym, INTSXP, (B->n) + 1)),
	xnz = 10 * B->p[B->n];	/* initial estimate of nnz in x */
    int *ti = Calloc(xnz, int), k, lo = uplo_P(a)[0] == 'L', pos = 0;
    double *tx = Calloc(xnz, double);
    double  *wrk = Alloca(A->n, double);
    int *xi = Alloca(2*A->n, int);	/* for cs_reach */
    R_CheckStack();

    if (A->m != A->n || B->n < 1 || A->n < 1 || A->n != B->m)
	error(_("Dimensions of system to be solved are inconsistent"));
    slot_dup(ans, b, Matrix_DimSym);
    SET_DimNames(ans, b);
    xp[0] = 0;
    for (k = 0; k < B->n; k++) {
	int top = cs_spsolve (A, B, k, xi, wrk, (int *)NULL, lo);
	int nz = A->n - top, p;

	xp[k + 1] = nz + xp[k];
	if (xp[k + 1] > xnz) {
	    while (xp[k + 1] > xnz) xnz *= 2;
	    ti = Realloc(ti, xnz, int);
	    tx = Realloc(tx, xnz, double);
	}
	if (lo)			/* increasing row order */
	    for(p = top; p < A->n; p++, pos++) {
		ti[pos] = xi[p];
		tx[pos] = wrk[xi[p]];
	    }
	else			/* decreasing order, reverse copy */
	    for(p = A->n - 1; p >= top; p--, pos++) {
		ti[pos] = xi[p];
		tx[pos] = wrk[xi[p]];
	    }
    }
    xnz = xp[B->n];
    Memcpy(INTEGER(ALLOC_SLOT(ans, Matrix_iSym, INTSXP,  xnz)), ti, xnz);
    Memcpy(   REAL(ALLOC_SLOT(ans, Matrix_xSym, REALSXP, xnz)), tx, xnz);

    Free(ti); Free(tx);
    UNPROTECT(1);
    return ans;
}