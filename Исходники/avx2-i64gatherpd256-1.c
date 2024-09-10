void extern
avx2_test (void)
{
  x = _mm256_i64gather_pd (base, idx, 1);
}