double entropia (double *Ni, int n) {
  double N = 0, S = 0;

  for (int i = 0; i < n; i++) {
    N += Ni [i];
    S -= lgamma (Ni[i] + 1);
  }
  S += lgamma (N + 1) - N * log ((double)n);
  return S;
}