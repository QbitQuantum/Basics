static void initialize_circulant(hbhankel_matrix *h,
                                 const double *F,
                                 R_len_t rank,
                                 const R_len_t *N,
                                 const R_len_t *L,
                                 const int *circular) {
  fftw_complex *ocirc;
  fftw_plan p1, p2;
  double *circ;
  R_len_t *revN, r;

  /* Allocate needed memory */
  circ = (double*) fftw_malloc(prod(rank, N) * sizeof(double));
  ocirc = (fftw_complex*) fftw_malloc(hprod(rank, N) * sizeof(fftw_complex));

  /* Estimate the best plans for given input length, note, that input data is
     stored in column-major mode, that's why we're passing dimensions in
     *reverse* order */
  revN = Calloc(rank, R_len_t);
  for (r = 0; r < rank; ++r) revN[r] = N[rank - 1 - r];
  p1 = fftw_plan_dft_r2c(rank, revN, circ, ocirc, FFTW_ESTIMATE);
  p2 = fftw_plan_dft_c2r(rank, revN, ocirc, circ, FFTW_ESTIMATE);
  Free(revN);

  /* Fill input buffer */
  memcpy(circ, F, prod(rank, N) * sizeof(double));

  /* Run the plan on input data */
  fftw_execute(p1);

  /* Cleanup and return */
  fftw_free(circ);

  h->circ_freq = ocirc;
  h->r2c_plan = p1;
  h->c2r_plan = p2;

  h->rank = rank;

  h->window = Calloc(rank, R_len_t);
  memcpy(h->window, L, rank * sizeof(R_len_t));

  h->length = Calloc(rank, R_len_t);
  memcpy(h->length, N, rank * sizeof(R_len_t));

  h->factor = Calloc(rank, R_len_t);
  for (r = 0; r < rank; ++r) h->factor[r] = circular[r] ? N[r] : N[r] - L[r] + 1;
}