void extern
avx512vl_test (void)
{
    x256 = _mm256_mask_slli_epi64 (x256, m256, x256, y);
    x256 = _mm256_maskz_slli_epi64 (m256, x256, y);
    x128 = _mm_mask_slli_epi64 (x128, m128, x128, y);
    x128 = _mm_maskz_slli_epi64 (m128, x128, y);
}