void nfft_benchomp_createdataset(unsigned int d, unsigned int trafo_adjoint, int *N, int M, double sigma)
{
  int n[d];
  int t, j;
  R *x;
  C *f, *f_hat;
  int N_total = 1;

  for (t = 0; t < d; t++)
    N_total *= N[t];

  x = (R*) NFFT(malloc)(d*M*sizeof(R));
  f = (C*) NFFT(malloc)(M*sizeof(C));
  f_hat = (C*) NFFT(malloc)(N_total*sizeof(C));

  for (t=0; t<d; t++)
    n[t] = sigma*NFFT(next_power_of_2)(N[t]);

  /** init pseudo random nodes */
  NFFT(vrand_shifted_unit_double)(x,d*M);
 
  if (trafo_adjoint==0)
  {
    NFFT(vrand_unit_complex)(f_hat,N_total);
  }
  else
  {
    NFFT(vrand_unit_complex)(f,M);
  }

  printf("%d %d ", d, trafo_adjoint);

  for (t=0; t<d; t++)
    printf("%d ", N[t]);

  for (t=0; t<d; t++)
    printf("%d ", n[t]);

  printf("%d\n", M);

  for (j=0; j < M; j++)
  {
    for (t=0; t < d; t++)
      printf("%.16e ", x[d*j+t]);
    printf("\n");
  }

  if (trafo_adjoint==0)
  {
    for (j=0; j < N_total; j++)
      printf("%.16e %.16e\n", creal(f_hat[j]), cimag(f_hat[j]));
  }
  else
  {
    for (j=0; j < M; j++)
      printf("%.16e %.16e\n", creal(f[j]), cimag(f[j]));
  }

  NFFT(free)(x);
  NFFT(free)(f);
  NFFT(free)(f_hat);
}