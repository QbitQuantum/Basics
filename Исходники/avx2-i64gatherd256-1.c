void extern
avx2_test (void)
{
  x = _mm256_i64gather_epi32 (base, idx, 1);
}