void extern
avx512f_test (void)
{
  x = _mm512_max_pd (x, x);
  x = _mm512_mask_max_pd (x, m, x, x);
  x = _mm512_maskz_max_pd (m, x, x);
  x = _mm512_max_round_pd (x, x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_max_round_pd (x, m, x, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_max_round_pd (m, x, x, _MM_FROUND_NO_EXC);
}