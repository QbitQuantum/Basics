void extern
avx2_test (void)
{
  x = _mm256_sign_epi8 (x, x);
}