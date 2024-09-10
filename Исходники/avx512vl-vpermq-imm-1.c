void extern
avx512vl_test (void)
{
  x = _mm256_mask_permutex_epi64 (x, m, x, 13);
  x = _mm256_maskz_permutex_epi64 (m, x, 13);
}