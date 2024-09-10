void extern
avx512f_test (void)
{
  x1 = _mm_mask_div_sd (x1, m, x2, x3);
  x1 = _mm_maskz_div_sd (m, x1, x2);
  x1 = _mm_div_round_sd (x1, x2, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  x1 = _mm_mask_div_round_sd (x1, m, x2, x3, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
  x1 = _mm_maskz_div_round_sd (m, x1, x2, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}