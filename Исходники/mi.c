int make_mi(mi_t* const m, const int n, const int k) {
  if (n < k) return 0;

  m->k = k;
  m->n = n;
  init_psi(m);
  m->sxs  = Calloc(n, coord_t);
  m->xiis = Calloc(n, int);
  m->sys  = Calloc(n, coord_t);
  m->yiis = Calloc(n, int);

  return 1;
}