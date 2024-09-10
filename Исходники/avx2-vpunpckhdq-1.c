void extern
avx2_test (void)
{
  x = _mm256_unpackhi_epi32 (x, x);
}