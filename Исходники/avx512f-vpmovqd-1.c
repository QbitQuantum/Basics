void extern
avx512f_test (void)
{
  res = _mm512_cvtepi64_epi32 (s);
  res = _mm512_mask_cvtepi64_epi32 (res, m, s);
  res = _mm512_maskz_cvtepi64_epi32 (m, s);
  _mm512_mask_cvtepi64_storeu_epi32 ((void *) &res, m, s);
}