void extern
avx512f_test (void)
{
  x = _mm512_div_ps (x, x);
  x = _mm512_mask_div_ps (x, m, x, x);
  x = _mm512_maskz_div_ps (m, x, x);
  x = _mm512_div_round_ps (x, x, _MM_FROUND_TO_NEAREST_INT);
  x = _mm512_mask_div_round_ps (x, m, x, x, _MM_FROUND_TO_POS_INF);
  x = _mm512_maskz_div_round_ps (m, x, x, _MM_FROUND_TO_ZERO);
}