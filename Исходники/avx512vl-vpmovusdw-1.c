void extern
avx512vl_test (void)
{
  z = _mm_cvtusepi32_epi16 (x);
  z = _mm_mask_cvtusepi32_epi16 (z, m, x);
  z = _mm_maskz_cvtusepi32_epi16 (m, x);
  z = _mm256_cvtusepi32_epi16 (y);
  z = _mm256_mask_cvtusepi32_epi16 (z, m, y);
  z = _mm256_maskz_cvtusepi32_epi16 (m, y);
}