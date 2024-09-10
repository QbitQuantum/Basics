void extern
avx512vl_test (void)
{
  x = _mm256_mask_broadcastq_epi64 (x, m, y);
  x = _mm256_maskz_broadcastq_epi64 (m, y);
  y = _mm_mask_broadcastq_epi64 (y, m, y);
  y = _mm_maskz_broadcastq_epi64 (m, y);

  x = _mm256_mask_set1_epi64 (x, m, z);
  x = _mm256_maskz_set1_epi64 (m, z);
  y = _mm_mask_set1_epi64 (y, m, z);
  y = _mm_maskz_set1_epi64 (m, z);
}