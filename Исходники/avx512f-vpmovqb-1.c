void extern
avx512f_test (void)
{
  res = _mm512_cvtepi64_epi8 (s);
  res = _mm512_mask_cvtepi64_epi8 (res, m, s);
  res = _mm512_maskz_cvtepi64_epi8 (m, s);
  _mm512_mask_cvtepi64_storeu_epi8 ((void *) &res, m, s);
}