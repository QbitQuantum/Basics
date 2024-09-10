void extern
avx512vl_test (void)
{
  x = _mm256_maskz_permutexvar_epi64 (m, x, x);
  x = _mm256_mask_permutexvar_epi64 (x, m, x, x);
}