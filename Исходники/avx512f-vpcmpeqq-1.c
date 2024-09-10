void extern
avx512f_test (void)
{
  m = _mm512_cmpeq_epi64_mask (x, x);
  m = _mm512_mask_cmpeq_epi64_mask (3, x, x);
}