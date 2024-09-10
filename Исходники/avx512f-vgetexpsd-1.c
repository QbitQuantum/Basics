void extern
avx512f_test (void)
{
  x = _mm_getexp_sd (x, x);
  x = _mm_getexp_round_sd (x, x, _MM_FROUND_NO_EXC);
}