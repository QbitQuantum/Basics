void extern
avx2_test (void)
{
  x = _mm256_sign_epi32 (x, x);
}