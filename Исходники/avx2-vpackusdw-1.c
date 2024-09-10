void extern
avx2_test (void)
{
  x = _mm256_packus_epi32 (x, x);
}