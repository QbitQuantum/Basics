static PetscErrorCode PetscDTGaussJacobiQuadrature1D_Internal(PetscInt npoints, PetscReal a, PetscReal b, PetscReal *x, PetscReal *w)
{
  PetscInt       maxIter = 100;
  PetscReal      eps     = 1.0e-8;
  PetscReal      a1, a2, a3, a4, a5, a6;
  PetscInt       k;
  PetscErrorCode ierr;

  PetscFunctionBegin;

  a1      = pow(2, a+b+1);
#if defined(PETSC_HAVE_TGAMMA)
  a2      = tgamma(a + npoints + 1);
  a3      = tgamma(b + npoints + 1);
  a4      = tgamma(a + b + npoints + 1);
#else
  SETERRQ(PETSC_COMM_SELF,PETSC_ERR_SUP,"tgamma() - math routine is unavailable.");
#endif

  ierr = PetscDTFactorial_Internal(npoints, &a5);CHKERRQ(ierr);
  a6   = a1 * a2 * a3 / a4 / a5;
  /* Computes the m roots of P_{m}^{a,b} on [-1,1] by Newton's method with Chebyshev points as initial guesses.
   Algorithm implemented from the pseudocode given by Karniadakis and Sherwin and Python in FIAT */
  for (k = 0; k < npoints; ++k) {
    PetscReal r = -cos((2.0*k + 1.0) * PETSC_PI / (2.0 * npoints)), dP;
    PetscInt  j;

    if (k > 0) r = 0.5 * (r + x[k-1]);
    for (j = 0; j < maxIter; ++j) {
      PetscReal s = 0.0, delta, f, fp;
      PetscInt  i;

      for (i = 0; i < k; ++i) s = s + 1.0 / (r - x[i]);
      ierr = PetscDTComputeJacobi(a, b, npoints, r, &f);CHKERRQ(ierr);
      ierr = PetscDTComputeJacobiDerivative(a, b, npoints, r, &fp);CHKERRQ(ierr);
      delta = f / (fp - f * s);
      r     = r - delta;
      if (fabs(delta) < eps) break;
    }
    x[k] = r;
    ierr = PetscDTComputeJacobiDerivative(a, b, npoints, x[k], &dP);CHKERRQ(ierr);
    w[k] = a6 / (1.0 - PetscSqr(x[k])) / PetscSqr(dP);
  }
  PetscFunctionReturn(0);
}