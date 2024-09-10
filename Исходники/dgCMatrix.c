SEXP dgCMatrix_matrix_solve(SEXP Ap, SEXP b, SEXP give_sparse)
// FIXME:  add  'keep_dimnames' as argument
{
    Rboolean sparse = asLogical(give_sparse);
    if(sparse) {
	// FIXME: implement this
	error(_("dgCMatrix_matrix_solve(.., sparse=TRUE) not yet implemented"));

	/* Idea: in the  for(j = 0; j < nrhs ..) loop below, build the *sparse* result matrix
	 * ----- *column* wise -- which is perfect for dgCMatrix
	 * --> build (i,p,x) slots "increasingly" [well, allocate in batches ..]
	 *
	 * --> maybe first a protoype in R
	 */

    }
    SEXP ans = PROTECT(dup_mMatrix_as_dgeMatrix(b)),
	lu, qslot;
    CSP L, U;
    int *bdims = INTEGER(GET_SLOT(ans, Matrix_DimSym)), *p, *q;
    int j, n = bdims[0], nrhs = bdims[1];
    double *x, *ax = REAL(GET_SLOT(ans, Matrix_xSym));
    C_or_Alloca_TO(x, n, double);

    if (isNull(lu = get_factors(Ap, "LU"))) {
	install_lu(Ap, /* order = */ 1, /* tol = */ 1.0, /* err_sing = */ TRUE,
		   /* keep_dimnames = */ TRUE);
	lu = get_factors(Ap, "LU");
    }
    qslot = GET_SLOT(lu, install("q"));
    L = AS_CSP__(GET_SLOT(lu, install("L")));
    U = AS_CSP__(GET_SLOT(lu, install("U")));
    R_CheckStack();
    if (U->n != n)
	error(_("Dimensions of system to be solved are inconsistent"));
    if(nrhs >= 1 && n >= 1) {
	p = INTEGER(GET_SLOT(lu, Matrix_pSym));
	q = LENGTH(qslot) ? INTEGER(qslot) : (int *) NULL;

	for (j = 0; j < nrhs; j++) {
	    cs_pvec(p, ax + j * n, x, n);  /* x = b(p) */
	    cs_lsolve(L, x);	       /* x = L\x */
	    cs_usolve(U, x);	       /* x = U\x */
	    if (q)		       /* r(q) = x , hence
					  r = Q' U{^-1} L{^-1} P b = A^{-1} b */
		cs_ipvec(q, x, ax + j * n, n);
	    else
		Memcpy(ax + j * n, x, n);
	}
    }
    if(n >= SMALL_4_Alloca) Free(x);
    UNPROTECT(1);
    return ans;
}