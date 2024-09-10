void extern
avx512vl_test (void)
{
    x = _mm256_broadcastss_ps (y);
    x = _mm256_mask_broadcastss_ps (x, m, y);
    x = _mm256_maskz_broadcastss_ps (m, y);
    y = _mm_broadcastss_ps (y);
    y = _mm_mask_broadcastss_ps (y, m, y);
    y = _mm_maskz_broadcastss_ps (m, y);
}