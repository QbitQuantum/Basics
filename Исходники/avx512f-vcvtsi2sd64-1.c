void extern
avx512f_test (void)
{
  x = _mm_cvt_roundi64_sd (x, n, _MM_FROUND_TO_POS_INF);
}