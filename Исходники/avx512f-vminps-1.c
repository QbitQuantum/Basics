void extern
avx512f_test (void)
{
    x = _mm512_min_ps (x, x);
    x = _mm512_mask_min_ps (x, m, x, x);
    x = _mm512_maskz_min_ps (m, x, x);
    x = _mm512_min_round_ps (x, x, _MM_FROUND_NO_EXC);
    x = _mm512_mask_min_round_ps (x, m, x, x, _MM_FROUND_NO_EXC);
    x = _mm512_maskz_min_round_ps (m, x, x, _MM_FROUND_NO_EXC);
}