void extern
avx512vl_test (void)
{
  x = _mm256_ror_epi64 (x, 11);
  x = _mm256_mask_ror_epi64 (x, m, x, 11);
  x = _mm256_maskz_ror_epi64 (m, x, 11);

  y = _mm_ror_epi64 (y, 12);
  y = _mm_mask_ror_epi64 (y, m, y, 12);
  y = _mm_maskz_ror_epi64 (m, y, 12);
}