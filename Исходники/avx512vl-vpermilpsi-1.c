void extern
avx512vl_test (void)
{
  y = _mm256_mask_permute_ps (y, m, y, 13);
  y = _mm256_maskz_permute_ps (m, y, 13);
  x = _mm_mask_permute_ps (x, m, x, 13);
  x = _mm_maskz_permute_ps (m, x, 13);
}