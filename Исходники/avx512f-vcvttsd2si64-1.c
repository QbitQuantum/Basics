void extern
avx512f_test (void)
{
    y = _mm_cvttsd_i64 (x);
    y = _mm_cvtt_roundsd_i64 (x, _MM_FROUND_NO_EXC);
}