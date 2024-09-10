void extern
avx512f_test (void)
{
  x = _mm512_add_ps (x, x);
  x = _mm512_mask_add_ps (x, m, x, x);
  x = _mm512_maskz_add_ps (m, x, x);
  x = _mm512_add_round_ps (x, x, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  x = _mm512_mask_add_round_ps (x, m, x, x, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
  x = _mm512_maskz_add_round_ps (m, x, x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}