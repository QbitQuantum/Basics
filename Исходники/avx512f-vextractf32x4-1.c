void extern
avx512f_test (void)
{
    y = _mm512_extractf32x4_ps (x, 1);
    y = _mm512_mask_extractf32x4_ps (y, 2, x, 1);
    y = _mm512_maskz_extractf32x4_ps (2, x, 1);
}