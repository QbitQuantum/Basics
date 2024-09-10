void extern
avx512f_test (void)
{
  x = _mm_scalef_ss (x, x);
  x = _mm_scalef_round_ss (x, x, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  x = _mm_mask_scalef_round_ss (x, m, x, x, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
  x = _mm_maskz_scalef_round_ss (m, x, x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}