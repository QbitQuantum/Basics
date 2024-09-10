void extern
avx512f_test (void)
{
  res = _mm512_cvtepi16_epi32 (s);
  res = _mm512_mask_cvtepi16_epi32 (res, m, s);
  res = _mm512_maskz_cvtepi16_epi32 (m, s);
}