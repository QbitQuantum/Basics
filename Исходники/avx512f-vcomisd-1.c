void extern
avx512f_test (void)
{
  res = _mm_comi_round_sd (x, x, _CMP_LT_OS, _MM_FROUND_NO_EXC);
}