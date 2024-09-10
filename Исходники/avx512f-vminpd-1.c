void extern
avx512f_test (void)
{
  x = _mm512_min_pd (x, x);
  x = _mm512_mask_min_pd (x, m, x, x);
  x = _mm512_maskz_min_pd (m, x, x);
  x = _mm512_min_round_pd (x, x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_min_round_pd (x, m, x, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_min_round_pd (m, x, x, _MM_FROUND_NO_EXC);
}