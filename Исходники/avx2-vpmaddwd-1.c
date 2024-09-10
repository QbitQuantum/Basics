void extern
avx2_test (void)
{
  x = _mm256_madd_epi16 (x, x);
}