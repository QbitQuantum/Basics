void extern
avx512f_test (void)
{
  y = _mm_cvtsd_u64 (x);
  y = _mm_cvt_roundsd_u64 (x, _MM_FROUND_TO_POS_INF);
}