void extern
avx512bw_test (void)
{
    z = _mm512_sllv_epi16 (z, z);
    z = _mm512_mask_sllv_epi16 (z, m1, z, z);
    z = _mm512_maskz_sllv_epi16 (m1, z, z);
    y = _mm256_sllv_epi16 (y, y);
    y = _mm256_mask_sllv_epi16 (y, m2, y, y);
    y = _mm256_maskz_sllv_epi16 (m2, y, y);
    x = _mm_sllv_epi16 (x, x);
    x = _mm_mask_sllv_epi16 (x, m3, x, x);
    x = _mm_maskz_sllv_epi16 (m3, x, x);
}