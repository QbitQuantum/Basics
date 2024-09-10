void extern
avx512vl_test (void)
{
  x1 = _mm256_mask2_permutex2var_ps (x1, y, m, x1);
  x2 = _mm_mask2_permutex2var_ps (x2, z, m, x2);
}