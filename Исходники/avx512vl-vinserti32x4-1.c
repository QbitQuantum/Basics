void extern
avx512vl_test (void)
{
  x = _mm256_inserti32x4 (x, y, 1);
  x = _mm256_mask_inserti32x4 (x, 2, x, y, 1);
  x = _mm256_maskz_inserti32x4 (2, x, y, 1);
}