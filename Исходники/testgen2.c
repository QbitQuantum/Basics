int
main(int argc, char *argv[])
{
  gen_workspace *gen_workspace_p;
  lapack_workspace *lapack_workspace_p;
  size_t N;
  int c;
  int lower;
  int upper;
  int incremental;
  size_t nmat;
  gsl_matrix *A, *B;
  gsl_rng *r;
  int s;
  int compute_schur;
  size_t i;

  gsl_ieee_env_setup();
  gsl_rng_env_setup();

  N = 30;
  lower = -10;
  upper = 10;
  incremental = 0;
  nmat = 0;
  compute_schur = 0;

  while ((c = getopt(argc, argv, "ic:n:l:u:z")) != (-1))
    {
      switch (c)
        {
          case 'i':
            incremental = 1;
            break;

          case 'n':
            N = strtol(optarg, NULL, 0);
            break;

          case 'l':
            lower = strtol(optarg, NULL, 0);
            break;

          case 'u':
            upper = strtol(optarg, NULL, 0);
            break;

          case 'c':
            nmat = strtoul(optarg, NULL, 0);
            break;

          case 'z':
            compute_schur = 1;
            break;

          case '?':
          default:
            printf("usage: %s [-i] [-z] [-n size] [-l lower-bound] [-u upper-bound] [-c num]\n", argv[0]);
            exit(1);
            break;
        } /* switch (c) */
    }

  A = gsl_matrix_alloc(N, N);
  B = gsl_matrix_alloc(N, N);
  gen_workspace_p = gen_alloc(N, compute_schur);
  lapack_workspace_p = lapack_alloc(N);

  r = gsl_rng_alloc(gsl_rng_default);

  if (incremental)
    {
      make_start_matrix(A, lower);

      /* we need B to be non-singular */
      make_random_integer_matrix(B, r, lower, upper);
    }

  fprintf(stderr, "testing N = %d", N);
  if (incremental)
    fprintf(stderr, " incrementally");
  else
    fprintf(stderr, " randomly");

  fprintf(stderr, " on element range [%d, %d]", lower, upper);

  if (compute_schur)
    fprintf(stderr, ", with Schur vectors");

  fprintf(stderr, "\n");

  while (1)
    {
      if (nmat && (count >= nmat))
        break;

      ++count;

      if (!incremental)
        {
          make_random_matrix(A, r, lower, upper);
          make_random_matrix(B, r, lower, upper);
        }
      else
        {
          s = inc_matrix(A, lower, upper);
          if (s)
            break; /* all done */

          make_random_integer_matrix(B, r, lower, upper);
        }

      /*if (count != 89120)
        continue;*/

      /* make copies of matrices */
      gsl_matrix_memcpy(gen_workspace_p->A, A);
      gsl_matrix_memcpy(gen_workspace_p->B, B);
      gsl_matrix_transpose_memcpy(lapack_workspace_p->A, A);
      gsl_matrix_transpose_memcpy(lapack_workspace_p->B, B);

      /* compute eigenvalues with LAPACK */
      s = lapack_proc(lapack_workspace_p);

      if (s != GSL_SUCCESS)
        {
          printf("LAPACK failed, case %lu\n", count);
          exit(1);
        }

#if 0
      print_matrix(A, "A");
      print_matrix(B, "B");
      gsl_matrix_transpose(lapack_workspace_p->A);
      gsl_matrix_transpose(lapack_workspace_p->B);
      print_matrix(lapack_workspace_p->A, "S_lapack");
      print_matrix(lapack_workspace_p->B, "T_lapack");
#endif

      /* compute eigenvalues with GSL */
      s = gen_proc(gen_workspace_p);

      if (s != GSL_SUCCESS)
        {
          printf("=========== CASE %lu ============\n", count);
          printf("Failed to converge: found %u eigenvalues\n",
                 gen_workspace_p->n_evals);
          print_matrix(A, "A");
          print_matrix(B, "B");
          print_matrix(gen_workspace_p->A, "Af");
          print_matrix(gen_workspace_p->B, "Bf");
          print_matrix(lapack_workspace_p->A, "Ae");
          print_matrix(lapack_workspace_p->B, "Be");
          exit(1);
        }

#if 0
      print_matrix(gen_workspace_p->A, "S_gsl");
      print_matrix(gen_workspace_p->B, "T_gsl");
#endif

      /* compute alpha / beta vectors */
      for (i = 0; i < N; ++i)
        {
          double beta;
          gsl_complex alpha, z;

          beta = gsl_vector_get(gen_workspace_p->beta, i);
          if (beta == 0.0)
            GSL_SET_COMPLEX(&z, GSL_POSINF, GSL_POSINF);
          else
            {
              alpha = gsl_vector_complex_get(gen_workspace_p->alpha, i);
              z = gsl_complex_div_real(alpha, beta);
            }

          gsl_vector_complex_set(gen_workspace_p->evals, i, z);

          beta = gsl_vector_get(lapack_workspace_p->beta, i);
          GSL_SET_COMPLEX(&alpha,
                          lapack_workspace_p->alphar[i],
                          lapack_workspace_p->alphai[i]);

          if (beta == 0.0)
            GSL_SET_COMPLEX(&z, GSL_POSINF, GSL_POSINF);
          else
            z = gsl_complex_div_real(alpha, beta);

          gsl_vector_complex_set(lapack_workspace_p->evals, i, z);
          gsl_vector_complex_set(lapack_workspace_p->alpha, i, alpha);
        }

#if 0
      gsl_sort_vector(gen_workspace_p->beta);
      gsl_sort_vector(lapack_workspace_p->beta);
      sort_complex_vector(gen_workspace_p->alpha);
      sort_complex_vector(lapack_workspace_p->alpha);

      s = test_alpha(gen_workspace_p->alpha,
                     lapack_workspace_p->alpha,
                     A,
                     B,
                     "gen",
                     "lapack");
      s = test_beta(gen_workspace_p->beta,
                    lapack_workspace_p->beta,
                    A,
                    B,
                    "gen",
                    "lapack");
#endif
#if 1
      sort_complex_vector(gen_workspace_p->evals);
      sort_complex_vector(lapack_workspace_p->evals);

      s = test_evals(gen_workspace_p->evals,
                     lapack_workspace_p->evals,
                     A,
                     B,
                     "gen",
                     "lapack");
#endif

      if (compute_schur)
        {
          test_schur(A,
                     gen_workspace_p->A,
                     gen_workspace_p->Q,
                     gen_workspace_p->Z);
          test_schur(B,
                     gen_workspace_p->B,
                     gen_workspace_p->Q,
                     gen_workspace_p->Z);
        }
    }

  gsl_matrix_free(A);
  gsl_matrix_free(B);
  gen_free(gen_workspace_p);
  lapack_free(lapack_workspace_p);

  if (r)
    gsl_rng_free(r);

  return 0;
} /* main() */