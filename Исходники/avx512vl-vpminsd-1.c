void extern
avx512vl_test (void)
{
  x = _mm256_mask_min_epi32 (x, m, x, x);
  x = _mm256_maskz_min_epi32 (m, x, x);
  y = _mm_mask_min_epi32 (y, m, y, y);
  y = _mm_maskz_min_epi32 (m, y, y);
}