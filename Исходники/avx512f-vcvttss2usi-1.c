void extern
avx512f_test (void)
{
  y = _mm_cvttss_u32 (x);
  y = _mm_cvtt_roundss_u32 (x, _MM_FROUND_NO_EXC);
}