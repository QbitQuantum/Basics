void extern
avx512f_test (void)
{
    x1 = _mm512_fmaddsub_ps (x1, x2, x3);
    x1 = _mm512_mask_fmaddsub_ps (x1, m, x2, x3);
    x3 = _mm512_mask3_fmaddsub_ps (x1, x2, x3, m);
    x1 = _mm512_maskz_fmaddsub_ps (m, x1, x2, x3);
    x1 = _mm512_fmaddsub_round_ps (x1, x2, x3, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    x1 = _mm512_mask_fmaddsub_round_ps (x1, m, x2, x3, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
    x3 = _mm512_mask3_fmaddsub_round_ps (x1, x2, x3, m, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
    x1 = _mm512_maskz_fmaddsub_round_ps (m, x1, x2, x3, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}