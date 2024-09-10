void extern
avx512f_test (void)
{
  _mm512_i64scatter_pd (addr, idx, src, 8);
  _mm512_mask_i64scatter_pd (addr, m8, idx, src, 8);
}