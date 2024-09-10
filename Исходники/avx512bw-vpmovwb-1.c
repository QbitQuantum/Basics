void extern
avx512bw_test (void)
{
  z = _mm_cvtepi16_epi8 (x);
  z = _mm_mask_cvtepi16_epi8 (z, m1, x);
  z = _mm_maskz_cvtepi16_epi8 (m1, x);
  z = _mm256_cvtepi16_epi8 (y);
  z = _mm256_mask_cvtepi16_epi8 (z, m2, y);
  z = _mm256_maskz_cvtepi16_epi8 (m2, y);
  y = _mm512_cvtepi16_epi8 (u);
  y = _mm512_mask_cvtepi16_epi8 (y, m3, u);
  y = _mm512_maskz_cvtepi16_epi8 (m3, u);
}