void extern
avx512vl_test (void)
{
  m = _mm_cmple_epu32_mask (x128, x128);
  m = _mm256_cmple_epu32_mask (x256, x256);
  m = _mm_mask_cmple_epu32_mask (3, x128, x128);
  m = _mm256_mask_cmple_epu32_mask (3, x256, x256);
}