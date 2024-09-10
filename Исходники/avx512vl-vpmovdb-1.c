void extern
avx512vl_test (void)
{
    z = _mm_cvtepi32_epi8 (x);
    z = _mm_mask_cvtepi32_epi8 (z, m, x);
    z = _mm_maskz_cvtepi32_epi8 (m, x);
    z = _mm256_cvtepi32_epi8 (y);
    z = _mm256_mask_cvtepi32_epi8 (z, m, y);
    z = _mm256_maskz_cvtepi32_epi8 (m, y);
}