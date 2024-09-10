void extern
avx512vl_test (void)
{
  y = _mm256_alignr_epi32 (y, y, 3);
  y = _mm256_mask_alignr_epi32 (y, m, y, y, 3);
  y = _mm256_maskz_alignr_epi32 (m, y, y, 3);

  x = _mm_alignr_epi32 (x, x, 3);
  x = _mm_mask_alignr_epi32 (x, m, x, x, 3);
  x = _mm_maskz_alignr_epi32 (m, x, x, 3);
}