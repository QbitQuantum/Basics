void extern
avx512f_test (void)
{
  res = _mm512_cvtusepi32_epi16 (s);
  res = _mm512_mask_cvtusepi32_epi16 (res, m, s);
  res = _mm512_maskz_cvtusepi32_epi16 (m, s);
}