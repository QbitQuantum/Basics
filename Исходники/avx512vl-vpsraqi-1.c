void extern
avx512vl_test (void)
{
  x256 = _mm256_srai_epi64 (x256, y);
  x256 = _mm256_mask_srai_epi64 (x256, m, x256, y);
  x256 = _mm256_maskz_srai_epi64 (m, x256, y);
  x128 = _mm_srai_epi64 (x128, y);
  x128 = _mm_mask_srai_epi64 (x128, m, x128, y);
  x128 = _mm_maskz_srai_epi64 (m, x128, y);
}