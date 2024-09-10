lh *lh_init_ia(char *name, int *h, int dim) {

  lh *x;
  int i;

  x = Calloc(1, sizeof(lh));
  x->name = name;
  x->h = Calloc(dim, sizeof(float));
  x->dim = dim;
  for (i = 0; i < x->dim; i++) {
    x->h[i] = (float) h[i];
    x->cnt += h[i];
  }
  x->outlyers = 0;
  return x;
}