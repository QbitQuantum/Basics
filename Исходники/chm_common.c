/* coerce a vector to REAL and copy the result to freshly R_alloc'd memory */
static void *RallocedREAL(SEXP x)
{
    SEXP rx = PROTECT(coerceVector(x, REALSXP));
    int lx = LENGTH(rx);
    /* We over-allocate the memory chunk so that it is never NULL. */
    /* The CHOLMOD code checks for a NULL pointer even in the length-0 case. */
    double *ans = Memcpy((double*)R_alloc(lx + 1, sizeof(double)),
			 REAL(rx), lx);
    UNPROTECT(1);
    return (void*)ans;
}