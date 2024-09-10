void extern
avx512f_test (void)
{
  y = _mm_cvt_roundsd_i32 (x, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}