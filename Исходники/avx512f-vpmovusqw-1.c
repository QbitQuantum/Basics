void extern
avx512f_test (void)
{
  res = _mm512_cvtusepi64_epi16 (s);
  res = _mm512_mask_cvtusepi64_epi16 (res, m, s);
  res = _mm512_maskz_cvtusepi64_epi16 (m, s);
  _mm512_mask_cvtusepi64_storeu_epi16 ((void *) &res, m, s);
}