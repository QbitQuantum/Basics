void extern
avx512f_test (void)
{
  m = _mm512_cmpneq_epu64_mask (x, x);
  m = _mm512_mask_cmpneq_epu64_mask (m, x, x);
}