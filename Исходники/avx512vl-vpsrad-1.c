void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_sra_epi32 (x256, m, x256, y);
  x256 = _mm256_maskz_sra_epi32 (m, x256, y);
  x128 = _mm_mask_sra_epi32 (x128, m, x128, y);
  x128 = _mm_maskz_sra_epi32 (m, x128, y);
}