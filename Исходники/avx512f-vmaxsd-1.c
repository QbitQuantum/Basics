void extern
avx512f_test (void)
{
  x1 = _mm_max_round_sd (x1, x2, _MM_FROUND_NO_EXC);
}