void extern
avx512f_test (void)
{
  a = _mm_fmadd_round_sd (a, b, c, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}