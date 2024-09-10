void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_max_ps (x256, m8, x256, x256);
  x256 = _mm256_maskz_max_ps (m8, x256, x256);
  x128 = _mm_mask_max_ps (x128, m8, x128, x128);
  x128 = _mm_maskz_max_ps (m8, x128, x128);
}