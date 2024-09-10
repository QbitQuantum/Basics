void extern
avx512f_test (void)
{
  res = _mm512_cvtsepi32_epi16 (s);
  res = _mm512_mask_cvtsepi32_epi16 (res, m, s);
  res = _mm512_maskz_cvtsepi32_epi16 (m, s);
  _mm512_mask_cvtsepi32_storeu_epi16 ((void *) &res, m, s);
}