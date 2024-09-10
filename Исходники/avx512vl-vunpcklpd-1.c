void extern
avx512vl_test (void)
{
  yy = _mm256_mask_unpacklo_pd (yy, m, y2, y3);
  xx = _mm_mask_unpacklo_pd (xx, m, x2, x3);

  yy = _mm256_maskz_unpacklo_pd (m, y2, y3);
  xx = _mm_maskz_unpacklo_pd (m, x2, x3);
}