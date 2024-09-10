void extern
avx512f_test (void)
{
  x = _mm512_div_pd (x, x);
  x = _mm512_mask_div_pd (x, m, x, x);
  x = _mm512_maskz_div_pd (m, x, x);
  x = _mm512_div_round_pd (x, x, _MM_FROUND_TO_NEAREST_INT);
  x = _mm512_mask_div_round_pd (x, m, x, x, _MM_FROUND_TO_NEG_INF);
  x = _mm512_maskz_div_round_pd (m, x, x, _MM_FROUND_TO_ZERO);
}