void extern
avx512f_test (void)
{
  x = _mm512_min_epi32 (x, x);
  x = _mm512_mask_min_epi32 (x, m, x, x);
  x = _mm512_maskz_min_epi32 (m, x, x);
}