void extern
avx2_test (void)
{
  x = _mm256_unpacklo_epi16 (x, x);
}