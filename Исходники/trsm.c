int main(int argc, char **argv)
{
  armas_conf_t conf;
  armas_x_dense_t B0, A, B;

  int ok, opt;
  int N = 301;
  int verbose = 1;
  int fails = 0;
  DTYPE alpha = 1.0;
  DTYPE n0, n1;

  while ((opt = getopt(argc, argv, "vC:")) != -1) {
    switch (opt) {
    case 'v':
      verbose++;
      break;
    case 'C':
      Aconstant = STRTOF(optarg);
      break;
    default:
      fprintf(stderr, "usage: trsm [-P nproc] [size]\n");
      exit(1);
    }
  }
    
  if (optind < argc)
    N = atoi(argv[optind]);

  conf = *armas_conf_default();

  armas_x_init(&A, N, N);
  armas_x_init(&B, N, N);
  armas_x_init(&B0, N, N);
  
  // Upper triangular matrix
  armas_x_set_values(&A, one, ARMAS_UPPER);
  if (N < 10) {
    printf("A:\n"); armas_x_printf(stdout, "%8.1e", &A);
  }
    

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_LEFT, &conf);
  if (N < 10) {
    printf("A*B:\n"); armas_x_printf(stdout, "%8.1e", &B);
  }
  armas_x_solve_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_LEFT, &conf);
  if (N < 10) {
    printf("A.-1*B:\n"); armas_x_printf(stdout, "%8.1e", &B);
  }
  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, L|U|N), A, L|U|N)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_RIGHT, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_RIGHT, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, R|U|N), A, R|U|N)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_LEFT|ARMAS_TRANSA, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_LEFT|ARMAS_TRANSA, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, L|U|T), A, L|U|T)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_RIGHT|ARMAS_TRANSA, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_UPPER|ARMAS_RIGHT|ARMAS_TRANSA, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, R|U|T), A, R|U|T)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  // Lower triangular matrix
  armas_x_set_values(&A, one, ARMAS_LOWER);

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_LEFT, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_LEFT, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, L|L|N), A, L|L|N)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_RIGHT, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_RIGHT, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, R|L|N), A, R|L|N)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_LEFT|ARMAS_TRANSA, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_LEFT|ARMAS_TRANSA, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, L|L|T), A, L|L|T)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  armas_x_set_values(&B, one, ARMAS_NULL);
  armas_x_mcopy(&B0, &B);
  armas_x_mult_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_RIGHT|ARMAS_TRANSA, &conf);
  armas_x_solve_trm(&B, alpha, &A, ARMAS_LOWER|ARMAS_RIGHT|ARMAS_TRANSA, &conf);

  n0 = rel_error(&n1, &B, &B0, ARMAS_NORM_ONE, ARMAS_NONE, &conf);
  ok = n0 == 0.0 || isOK(n0, N) ? 1 : 0;
  printf("%6s: B = solve_trm(mult_trm(B, A, R|L|T), A, R|L|T)\n", PASS(ok));
  if (verbose > 0) {
    printf("   || rel error || : %e, [%d]\n", n0, ndigits(n0));
  }
  fails += 1 - ok;

  test_left_right(N, verbose);
  exit(fails);
}