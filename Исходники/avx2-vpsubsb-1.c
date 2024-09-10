void extern
avx2_test (void)
{
  x = _mm256_subs_epi8 (x, x);
}