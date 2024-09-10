void extern
avx512f_test (void)
{
  m = _mm512_cmpgt_epi32_mask (x, x);
  m = _mm512_mask_cmpgt_epi32_mask (3, x, x);
}