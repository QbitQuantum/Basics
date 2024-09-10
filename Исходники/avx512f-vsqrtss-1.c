void extern
avx512f_test (void)
{
  x1 = _mm_sqrt_round_ss (x1, x2, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  x1 = _mm_mask_sqrt_round_ss (x1, m, x1, x2, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
  x1 = _mm_maskz_sqrt_round_ss (m, x1, x2, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}