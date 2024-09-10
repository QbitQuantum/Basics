void extern
avx512dq_test (void)
{
  x1 = _mm_range_sd (x1, x2, 3);
  x1 = _mm_range_round_sd (x1, x2, 3, _MM_FROUND_NO_EXC);
}