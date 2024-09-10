void extern
avx512vl_test (void)
{
  res = _mm256_mask_cvttpd_epi32 (res, m, s1);
  res = _mm_mask_cvttpd_epi32 (res, m, s2);

  res = _mm256_maskz_cvttpd_epi32 (m, s1);
  res = _mm_maskz_cvttpd_epi32 (m, s2);
}