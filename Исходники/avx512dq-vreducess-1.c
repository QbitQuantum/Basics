void extern
avx512dq_test (void)
{
  x1 = _mm_reduce_ss (x1, x2, 123);
}