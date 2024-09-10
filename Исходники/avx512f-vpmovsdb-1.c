void extern
avx512f_test (void)
{
  res = _mm512_cvtsepi32_epi8 (s);
  res = _mm512_mask_cvtsepi32_epi8 (res, m, s);
  res = _mm512_maskz_cvtsepi32_epi8 (m, s);
  _mm512_mask_cvtsepi32_storeu_epi8 ((void *) &res, m, s);
}