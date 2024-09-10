void extern
avx512f_test (void)
{
    x = _mm512_min_epu64 (x, x);
    x = _mm512_mask_min_epu64 (x, m, x, x);
    x = _mm512_maskz_min_epu64 (m, x, x);
}