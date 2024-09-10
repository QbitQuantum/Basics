void extern
avx512f_test (void)
{
  m16 = _mm512_testn_epi32_mask (x, x);
  m16 = _mm512_mask_testn_epi32_mask (3, x, x);
}