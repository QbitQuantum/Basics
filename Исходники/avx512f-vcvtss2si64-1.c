void extern
avx512f_test (void)
{
  y = _mm_cvt_roundss_i64 (x, _MM_FROUND_TO_ZERO);
}