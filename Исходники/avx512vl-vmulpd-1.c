void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_mul_pd (x256, m, x256, x256);
  x256 = _mm256_maskz_mul_pd (m, x256, x256);
  x128 = _mm_mask_mul_pd (x128, m, x128, x128);
  x128 = _mm_maskz_mul_pd (m, x128, x128);
}