void extern
avx512f_test (void)
{
  x = _mm_fixupimm_sd (x, x, y, 3);
  x = _mm_mask_fixupimm_sd (x, m, x, y, 3);
  x = _mm_maskz_fixupimm_sd (m, x, x, y, 3);
  x = _mm_fixupimm_round_sd (x, x, y, 3, _MM_FROUND_NO_EXC);
  x = _mm_mask_fixupimm_round_sd (x, m, x, y, 3, _MM_FROUND_NO_EXC);
  x = _mm_maskz_fixupimm_round_sd (m, x, x, y, 3, _MM_FROUND_NO_EXC);
}