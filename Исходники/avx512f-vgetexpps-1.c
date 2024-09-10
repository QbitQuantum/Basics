void extern
avx512f_test (void)
{
  x = _mm512_getexp_ps (x);
  x = _mm512_mask_getexp_ps (x, m, x);
  x = _mm512_maskz_getexp_ps (m, x);
  x = _mm512_getexp_round_ps (x, _MM_FROUND_NO_EXC);
  x = _mm512_mask_getexp_round_ps (x, m, x, _MM_FROUND_NO_EXC);
  x = _mm512_maskz_getexp_round_ps (m, x, _MM_FROUND_NO_EXC);
}