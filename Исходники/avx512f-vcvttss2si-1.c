void extern
avx512f_test (void)
{
  y = _mm_cvttss_i32 (x);
  y = _mm_cvtt_roundss_i32 (x, _MM_FROUND_NO_EXC);
}