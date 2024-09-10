void extern
avx512f_test (void)
{
  x = _mm512_loadu_si512 (p);
  x = _mm512_mask_loadu_epi32 (x, m, p);
  x = _mm512_maskz_loadu_epi32 (m, p);

  _mm512_storeu_si512 (p, x);
  _mm512_mask_storeu_epi32 (p, m, x);
}