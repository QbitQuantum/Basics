void extern
avx512f_test (void)
{
  x = _mm512_sll_epi32 (x, y);
  x = _mm512_mask_sll_epi32 (x, m, x, y);
  x = _mm512_maskz_sll_epi32 (m, x, y);
}