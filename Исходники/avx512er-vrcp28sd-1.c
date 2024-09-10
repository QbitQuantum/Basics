void extern
avx512er_test (void)
{
  x = _mm_rcp28_sd (x, y);
  x = _mm_rcp28_round_sd (x, y, _MM_FROUND_NO_EXC);
}