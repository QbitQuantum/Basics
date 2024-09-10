void extern
avx512vl_test (void)
{
  m = _mm_cmpgt_epu64_mask (x128, x128);
  m = _mm256_cmpgt_epu64_mask (x256, x256);
  m = _mm_mask_cmpgt_epu64_mask (3, x128, x128);
  m = _mm256_mask_cmpgt_epu64_mask (3, x256, x256);
}