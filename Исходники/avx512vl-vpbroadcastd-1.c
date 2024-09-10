void extern
avx512vl_test (void)
{
  x = _mm256_mask_broadcastd_epi32 (x, m, y);
  x = _mm256_maskz_broadcastd_epi32 (m, y);
  y = _mm_mask_broadcastd_epi32 (y, m, y);
  y = _mm_maskz_broadcastd_epi32 (m, y);

  x = _mm256_mask_set1_epi32 (x, m, z);
  x = _mm256_maskz_set1_epi32 (m, z);
  y = _mm_mask_set1_epi32 (y, m, z);
  y = _mm_maskz_set1_epi32 (m, z);
}