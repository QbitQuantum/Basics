void extern
avx512bw_test (void)
{
  z = _mm512_srli_epi16 (z, 13);
  z = _mm512_mask_srli_epi16 (z, m1, z, 13);
  z = _mm512_maskz_srli_epi16 (m1, z, 13);
  y = _mm256_mask_srli_epi16 (y, m2, y, 13);
  y = _mm256_maskz_srli_epi16 (m2, y, 13);
  x = _mm_mask_srli_epi16 (x, m3, x, 13);
  x = _mm_maskz_srli_epi16 (m3, x, 13);
}