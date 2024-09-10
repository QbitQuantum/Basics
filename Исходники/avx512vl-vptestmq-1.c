void extern
avx512vl_test (void)
{
  m = _mm_test_epi64_mask (x128, x128);
  m = _mm256_test_epi64_mask (x256, x256);
  m = _mm_mask_test_epi64_mask (3, x128, x128);
  m = _mm256_mask_test_epi64_mask (3, x256, x256);
}