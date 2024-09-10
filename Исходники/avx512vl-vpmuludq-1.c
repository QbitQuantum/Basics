void extern
avx512vl_test (void)
{
  x = _mm256_mask_mul_epu32 (x, m, x, x);
  x = _mm256_maskz_mul_epu32 (m, x, x);
  y = _mm_mask_mul_epu32 (y, m, y, y);
  y = _mm_maskz_mul_epu32 (m, y, y);
}