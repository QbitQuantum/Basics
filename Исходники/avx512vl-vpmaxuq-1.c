void extern
avx512vl_test (void)
{
  x = _mm256_max_epu64 (x, x);
  x = _mm256_mask_max_epu64 (x, m, x, x);
  x = _mm256_maskz_max_epu64 (m, x, x);
  y = _mm_max_epu64 (y, y);
  y = _mm_mask_max_epu64 (y, m, y, y);
  y = _mm_maskz_max_epu64 (m, y, y);
}