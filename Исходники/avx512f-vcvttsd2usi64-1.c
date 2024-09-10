void extern
avx512f_test (void)
{
  y = _mm_cvttsd_u64 (x);
  y = _mm_cvtt_roundsd_u64 (x, _MM_FROUND_NO_EXC);
}