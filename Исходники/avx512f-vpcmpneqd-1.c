void extern
avx512f_test (void)
{
  m = _mm512_cmpneq_epi32_mask (x, x);
  m = _mm512_mask_cmpneq_epi32_mask (m, x, x);
}