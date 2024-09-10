void extern
avx512vl_test (void)
{
  z1 = _mm256_mask_cvtps_epi32 (z1, m, x1);
  z1 = _mm256_maskz_cvtps_epi32 (m, x1);
  z2 = _mm_mask_cvtps_epi32 (z2, m, x2);
  z2 = _mm_maskz_cvtps_epi32 (m, x2);
}