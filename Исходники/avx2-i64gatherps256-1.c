void extern
avx2_test (void)
{
  x = _mm256_i64gather_ps (base, idx, 1);
}