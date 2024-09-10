void extern
avx512f_test (void)
{
  y = _mm_cvttss_i64 (x);
  y = _mm_cvtt_roundss_i64 (x, _MM_FROUND_NO_EXC);
}