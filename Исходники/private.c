scs_int solveLinSys(const AMatrix * A, const Settings * stgs, Priv * p, scs_float * b, const scs_float * s, scs_int iter) {
	scs_int cgIts;
	scs_float cgTol = calcNorm(b, A->n)
			* (iter < 0 ? CG_BEST_TOL : CG_MIN_TOL / POWF((scs_float) iter + 1, stgs->cg_rate));

	tic(&linsysTimer);
	/* solves Mx = b, for x but stores result in b */
	/* s contains warm-start (if available) */
	accumByAtrans(A, p, &(b[A->n]), b);
	/* solves (I+A'A)x = b, s warm start, solution stored in b */
	cgIts = pcg(A, stgs, p, s, b, A->n, MAX(cgTol, CG_BEST_TOL));
	scaleArray(&(b[A->n]), -1, A->m);
	accumByA(A, p, b, &(b[A->n]));

	if (iter >= 0) {
		totCgIts += cgIts;
	}

	totalSolveTime += tocq(&linsysTimer);
#if EXTRAVERBOSE > 0
	scs_printf("linsys solve time: %1.2es\n", tocq(&linsysTimer) / 1e3);
#endif
	return 0;
}