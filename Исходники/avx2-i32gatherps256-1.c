void extern
avx2_test (void)
{
  x = _mm256_i32gather_ps (base, idx, 1);
}