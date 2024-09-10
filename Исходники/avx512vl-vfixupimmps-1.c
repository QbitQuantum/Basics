void extern
avx512vl_test (void)
{
  xx = _mm256_fixupimm_ps (xx, xx, yy, 3);
  xx = _mm256_mask_fixupimm_ps (xx, m, xx, yy, 3);
  xx = _mm256_maskz_fixupimm_ps (m, xx, xx, yy, 3);
  x2 = _mm_fixupimm_ps (x2, x2, y2, 3);
  x2 = _mm_mask_fixupimm_ps (x2, m, x2, y2, 3);
  x2 = _mm_maskz_fixupimm_ps (m, x2, x2, y2, 3);
}