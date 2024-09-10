void extern
avx512er_test (void)
{
  x = _mm_rcp28_ss (x, y);
  x = _mm_rcp28_round_ss (x, y, _MM_FROUND_NO_EXC);
}