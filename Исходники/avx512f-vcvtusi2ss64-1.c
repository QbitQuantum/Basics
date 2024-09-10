void extern
avx512f_test (void)
{
  x = _mm_cvtu64_ss (x, n);
  x = _mm_cvt_roundu64_ss (x, n, _MM_FROUND_TO_ZERO);
}