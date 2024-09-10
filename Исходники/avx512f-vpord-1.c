void extern
avx512f_test (void)
{
  x = _mm512_or_si512 (x, x);
  x = _mm512_or_epi32 (x, x);
  x = _mm512_mask_or_epi32 (x, m, x, x);
  x = _mm512_maskz_or_epi32 (m, x, x);
}