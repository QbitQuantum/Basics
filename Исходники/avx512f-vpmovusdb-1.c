void extern
avx512f_test (void)
{
    res = _mm512_cvtusepi32_epi8 (s);
    res = _mm512_mask_cvtusepi32_epi8 (res, m, s);
    res = _mm512_maskz_cvtusepi32_epi8 (m, s);
    _mm512_mask_cvtusepi32_storeu_epi8 ((void *) &res, m, s);
}