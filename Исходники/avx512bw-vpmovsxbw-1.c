void extern
avx512bw_test (void)
{
  res1 = _mm512_cvtepi8_epi16 (s1);

  res1 = _mm512_mask_cvtepi8_epi16 (res1, m32, s1);
  res2 = _mm256_mask_cvtepi8_epi16 (res2, m16, s2);
  res3 = _mm_mask_cvtepi8_epi16 (res3, m8, s2);

  res1 = _mm512_maskz_cvtepi8_epi16 (m32, s1);
  res2 = _mm256_maskz_cvtepi8_epi16 (m16, s2);
  res3 = _mm_maskz_cvtepi8_epi16 (m8, s2);
}