void extern
avx2_test (void)
{
  x = _mm256_min_epu8 (x, x);
}