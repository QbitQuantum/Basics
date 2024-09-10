void extern
avx512bw_test (void)
{
  x = _mm512_sll_epi16 (x, y);
  x = _mm512_mask_sll_epi16 (x, m, x, y);
  x = _mm512_maskz_sll_epi16 (m, x, y);
  x256 = _mm256_mask_sll_epi16 (x256, m256, x256, y);
  x256 = _mm256_maskz_sll_epi16 (m256, x256, y);
  x128 = _mm_mask_sll_epi16 (x128, m128, x128, y);
  x128 = _mm_maskz_sll_epi16 (m128, x128, y);
}