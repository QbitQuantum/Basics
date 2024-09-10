void extern
avx512vl_test (void)
{
  x1 = _mm256_rcp14_pd (x1);
  x2 = _mm_rcp14_pd (x2);

  x1 = _mm256_mask_rcp14_pd (x1, m, x1);
  x2 = _mm_mask_rcp14_pd (x2, m, x2);

  x1 = _mm256_maskz_rcp14_pd (m, x1);
  x2 = _mm_maskz_rcp14_pd (m, x2);
}