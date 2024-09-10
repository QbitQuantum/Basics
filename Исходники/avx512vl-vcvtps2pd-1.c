void extern
avx512vl_test (void)
{
  res1 = _mm256_mask_cvtps_pd (res1, m, s);
  res2 = _mm_mask_cvtps_pd (res2, m, s);

  res1 = _mm256_maskz_cvtps_pd (m, s);
  res2 = _mm_maskz_cvtps_pd (m, s);
}