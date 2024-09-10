void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_srlv_epi32 (x256, m, x256, y256);
  x256 = _mm256_maskz_srlv_epi32 (m, x256, y256);
  x128 = _mm_mask_srlv_epi32 (x128, m, x128, y128);
  x128 = _mm_maskz_srlv_epi32 (m, x128, y128);
}