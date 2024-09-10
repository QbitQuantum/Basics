void extern
avx2_test (void)
{
  x = _mm256_sad_epu8 (x, x);
}