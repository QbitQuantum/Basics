void extern
avx512f_test (void)
{
  x = _mm512_max_ps (x, x);
  x = _mm512_mask_max_ps (x, m, x, x);
  x = _mm512_maskz_max_ps (m, x, x);
  x = _mm512_max_round_ps (x, x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_max_round_ps (x, m, x, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_max_round_ps (m, x, x, _MM_FROUND_NO_EXC);
}