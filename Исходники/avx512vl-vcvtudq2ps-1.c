void extern
avx512vl_test (void)
{
  res1 = _mm256_cvtepu32_ps (s1);
  res2 = _mm_cvtepu32_ps (s2);

  res1 = _mm256_mask_cvtepu32_ps (res1, m, s1);
  res2 = _mm_mask_cvtepu32_ps (res2, m, s2);

  res1 = _mm256_maskz_cvtepu32_ps (m, s1);
  res2 = _mm_maskz_cvtepu32_ps (m, s2);
}