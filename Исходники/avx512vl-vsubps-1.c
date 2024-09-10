void extern
avx512vl_test (void)
{
  x128 = _mm_mask_sub_ps (x128, m, x128, x128);
  x128 = _mm_maskz_sub_ps (m, x128, x128);

  x256 = _mm256_mask_sub_ps (x256, m, x256, x256);
  x256 = _mm256_maskz_sub_ps (m, x256, x256);
}