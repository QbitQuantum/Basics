void regressMinRelError_fr(int n, int m, mpfr_t **x, mpfr_t *result) {
  int m0 = n * 3, n0 = m + 2 * n, i, j;
  mpfr_t **a0, *c0, *result0;
  int in0[m0];

  a0 = malloc(sizeof(mpfr_t *) * m0);
  for(i=0;i<m0;i++) {
    a0[i] = calloc(n0+1, sizeof(mpfr_t));
    for(j=0;j<n0+1;j++) mpfr_zinit(a0[i][j]);
  }

  c0 = calloc(n0+1, sizeof(mpfr_t));
  result0 = calloc(n0+1, sizeof(mpfr_t));

  for(j=0;j<n0+1;j++) {
    mpfr_zinit(c0[j]);
    mpfr_zinit(result0[j]);
  }
  
  for(i=0;i<n;i++) {
    long double ld = mpfr_get_ld(x[m][i], GMP_RNDN);
    if (ld < DBL_MIN) ld = 1;

#if 1
    mpfr_set_ld(c0[m+i  +1], 1.0/fabsl(ld), GMP_RNDN);
    mpfr_set_ld(c0[m+n+i+1], 1.0/fabsl(ld), GMP_RNDN);
#else
    int e;
    frexpl(ld, &e);
    ld = 1.0 / ldexpl(1.0, e);
    mpfr_set_ld(c0[m+i  +1], ld, GMP_RNDN);
    mpfr_set_ld(c0[m+n+i+1], ld, GMP_RNDN);
#endif
    
    mpfr_set_d(a0[i*3+0][m+i+1], 1, GMP_RNDN);
    in0[i*3+0] = GEQ;

    mpfr_set_d(a0[i*3+1][m+n+i+1], 1, GMP_RNDN);
    in0[i*3+1] = GEQ;

    for(j=0;j<m;j++) {
      mpfr_set(a0[i*3+2][j+1], x[j][i], GMP_RNDN);
    }

    mpfr_set_d(a0[i*3+2][m+i+1], 1, GMP_RNDN);
    mpfr_set_d(a0[i*3+2][m+n+i+1], -1, GMP_RNDN);
    in0[i*3+2] = EQU;
    mpfr_set(a0[i*3+2][0], x[m][i], GMP_RNDN);
    mpfr_neg(a0[i*3+2][0], a0[i*3+2][0], GMP_RNDN);
  }

  int status = solve_fr(result0, n0, m0, a0, in0, c0);

  if (status == NOT_FEASIBLE) {
    printf("not feasible\n");
  } else {
    if (status == MAXIMIZABLE_TO_INFINITY) printf("maximizable to inf\n");
  }

  for(i=0;i<m;i++) {
    mpfr_set(result[i], result0[i+1], GMP_RNDN);
  }

  free(result0);
  free(c0);
}