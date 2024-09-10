void extern
avx512f_test (void)
{
  x = _mm512_ror_epi32 (x, 12);
  x = _mm512_mask_ror_epi32 (x, m, x, 12);
  x = _mm512_maskz_ror_epi32 (m, x, 12);
}