void extern
avx2_test (void)
{
  x = _mm256_permutevar8x32_epi32 (x, x);
}