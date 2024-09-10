static void makect_32(void) {
  float *c = rdft_w + 32;
  const int nc = 32;
  int j, nch;
  float delta;

  ip[1] = nc;
  nch = nc >> 1;
  delta = atanf(1.0f) / nch;
  c[0] = cosf(delta * nch);
  c[nch] = 0.5f * c[0];
  for (j = 1; j < nch; j++) {
    c[j] = 0.5f * cosf(delta * j);
    c[nc - j] = 0.5f * sinf(delta * j);
  }
}