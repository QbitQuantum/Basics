void extern
avx512vl_test (void)
{
    yy = _mm256_mask_unpackhi_ps (yy, m, y2, y3);
    xx = _mm_mask_unpackhi_ps (xx, m, x2, x3);

    yy = _mm256_maskz_unpackhi_ps (m, y2, y3);
    xx = _mm_maskz_unpackhi_ps (m, x2, x3);
}