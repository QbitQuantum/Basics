int riv_nbits(int nof_prb) {
  return (int) ceilf(log2f((float) nof_prb * ((float) nof_prb + 1) / 2));
}