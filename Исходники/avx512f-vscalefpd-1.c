void extern
avx512f_test (void)
{
    x = _mm512_scalef_pd (x, x);
    x = _mm512_mask_scalef_pd (x, m, x, x);
    x = _mm512_maskz_scalef_pd (m, x, x);
    x = _mm512_scalef_round_pd (x, x, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
    x = _mm512_mask_scalef_round_pd (x, m, x, x, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
    x = _mm512_maskz_scalef_round_pd (m, x, x, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}