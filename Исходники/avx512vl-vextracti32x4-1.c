void extern
avx512vl_test (void)
{
  y = _mm256_extracti32x4_epi32 (x, 1);
  y = _mm256_mask_extracti32x4_epi32 (y, 2, x, 1);
  y = _mm256_maskz_extracti32x4_epi32 (2, x, 1);
}