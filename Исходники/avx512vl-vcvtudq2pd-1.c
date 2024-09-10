void extern
avx512vl_test (void)
{
  res1 = _mm256_cvtepu32_pd (s);
  res2 = _mm_cvtepu32_pd (s);

  res1 = _mm256_mask_cvtepu32_pd (res1, m, s);
  res2 = _mm_mask_cvtepu32_pd (res2, m, s);

  res1 = _mm256_maskz_cvtepu32_pd (m, s);
  res2 = _mm_maskz_cvtepu32_pd (m, s);
}