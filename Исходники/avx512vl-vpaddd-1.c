void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_add_epi32 (x256, m8, x256, x256);
  x256 = _mm256_maskz_add_epi32 (m8, x256, x256);
  x128 = _mm_mask_add_epi32 (x128, m8, x128, x128);
  x128 = _mm_maskz_add_epi32 (m8, x128, x128);
}