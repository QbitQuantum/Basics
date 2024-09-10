void extern
avx512vl_test (void)
{
  x1 = _mm256_mask_expand_pd (x1, m, x1);
  x2 = _mm_mask_expand_pd (x2, m, x2);

  x1 = _mm256_maskz_expand_pd (m, x1);
  x2 = _mm_maskz_expand_pd (m, x2);

  x1 = _mm256_mask_expandloadu_pd (x1, m, p);
  x2 = _mm_mask_expandloadu_pd (x2, m, p);

  x1 = _mm256_maskz_expandloadu_pd (m, p);
  x2 = _mm_maskz_expandloadu_pd (m, p);
}