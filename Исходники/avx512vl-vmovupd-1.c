void extern
avx512vl_test (void)
{
  x1 = _mm256_mask_loadu_pd (x1, m, p);
  x2 = _mm_mask_loadu_pd (x2, m, p);

  x1 = _mm256_maskz_loadu_pd (m, p);
  x2 = _mm_maskz_loadu_pd (m, p);

  _mm256_mask_storeu_pd (p, m, x1);
  _mm_mask_storeu_pd (p, m, x2);
}