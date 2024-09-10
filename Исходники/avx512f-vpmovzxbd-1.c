void extern
avx512f_test (void)
{
  res = _mm512_cvtepu8_epi32 (s);
  res = _mm512_mask_cvtepu8_epi32 (res, m, s);
  res = _mm512_maskz_cvtepu8_epi32 (m, s);
}