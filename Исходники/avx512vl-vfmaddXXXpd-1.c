void extern
avx512vl_test (void)
{
  yy = _mm256_mask_fmadd_pd (yy, m, y2, y3);
  xx = _mm_mask_fmadd_pd (xx, m, x2, x3);

  y3 = _mm256_mask3_fmadd_pd (yy, y2, y3, m);
  x3 = _mm_mask3_fmadd_pd (xx, x2, x3, m);

  yy = _mm256_maskz_fmadd_pd (m, yy, y2, y3);
  xx = _mm_maskz_fmadd_pd (m, xx, x2, x3);
}