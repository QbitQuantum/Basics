void extern
avx512vl_test (void)
{
  yy = _mm256_mask_fmaddsub_ps (yy, m, y2, y3);
  xx = _mm_mask_fmaddsub_ps (xx, m, x2, x3);

  y3 = _mm256_mask3_fmaddsub_ps (yy, y2, y3, m);
  x3 = _mm_mask3_fmaddsub_ps (xx, x2, x3, m);

  yy = _mm256_maskz_fmaddsub_ps (m, yy, y2, y3);
  xx = _mm_maskz_fmaddsub_ps (m, xx, x2, x3);
}