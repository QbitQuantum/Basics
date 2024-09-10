void extern
avx512f_test (void)
{
  a = _mm_fnmsub_round_sd (a, b, c, _MM_FROUND_TO_NEAREST_INT);
}