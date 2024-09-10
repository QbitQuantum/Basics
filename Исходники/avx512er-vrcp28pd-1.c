void extern
avx512er_test (void)
{
  x = _mm512_rcp28_pd (x);
  x = _mm512_mask_rcp28_pd (x, m, x);
  x = _mm512_maskz_rcp28_pd (m, x);
  x = _mm512_rcp28_round_pd (x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_rcp28_round_pd (x, m, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_rcp28_round_pd (m, x, _MM_FROUND_NO_EXC);
}