void extern
avx512f_test (void)
{
  res = _mm512_cvtusepi64_epi32 (s);
  res = _mm512_mask_cvtusepi64_epi32 (res, m, s);
  res = _mm512_maskz_cvtusepi64_epi32 (m, s);
  _mm512_mask_cvtusepi64_storeu_epi32 ((void *) &res, m, s);
}