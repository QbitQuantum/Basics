/* Round scales to nearest 1/3.  This is necessary when using the Lim
 * & Stiehl DSS formulation. */
static void
round_scales (int n_scales, float *scales)
{
  for (int i = 0; i < n_scales; i++) {
    scales[i] = rintf (scales[i] * 3) / 3;
  }
}