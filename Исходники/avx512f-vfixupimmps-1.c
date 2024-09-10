void extern
avx512f_test (void)
{
  x1 = _mm512_fixupimm_ps (x1, x2, y, 3);
  x1 = _mm512_mask_fixupimm_ps (x1, m, x2, y, 3);
  x1 = _mm512_maskz_fixupimm_ps (m, x1, x2, y, 3);
  x1 = _mm512_fixupimm_round_ps (x1, x2, y, 3, _MM_FROUND_NO_EXC);
  x1 = _mm512_mask_fixupimm_round_ps (x1, m, x2, y, 3, _MM_FROUND_NO_EXC);
  x1 = _mm512_maskz_fixupimm_round_ps (m, x1, x2, y, 3, _MM_FROUND_NO_EXC);
}