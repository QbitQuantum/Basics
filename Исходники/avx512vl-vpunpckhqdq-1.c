void extern
avx512bw_test (void)
{
    x = _mm256_mask_unpackhi_epi64 (x, m, y, z);
    x = _mm256_maskz_unpackhi_epi64 (m, y, z);
    a = _mm_mask_unpackhi_epi64 (a, m, b, c);
    a = _mm_maskz_unpackhi_epi64 (m, b, c);
}