void extern
avx512vl_test (void)
{
  x256 = _mm256_scalef_ps (x256, x256);
  x256 = _mm256_mask_scalef_ps (x256, m8, x256, x256);
  x256 = _mm256_maskz_scalef_ps (m8, x256, x256);
  x128 = _mm_scalef_ps (x128, x128);
  x128 = _mm_mask_scalef_ps (x128, m8, x128, x128);
  x128 = _mm_maskz_scalef_ps (m8, x128, x128);
}