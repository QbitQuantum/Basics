void extern
avx512er_test (void)
{
  x = _mm512_rsqrt28_ps (x);
  x = _mm512_mask_rsqrt28_ps (x, m, x);
  x = _mm512_maskz_rsqrt28_ps (m, x);
  x = _mm512_rsqrt28_round_ps (x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_rsqrt28_round_ps (x, m, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_rsqrt28_round_ps (m, x, _MM_FROUND_NO_EXC);
}