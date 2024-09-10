void extern
avx2_test (void)
{
  x = _mm256_max_epi32 (x, x);
}