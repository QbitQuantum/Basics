void extern
avx512pf_test (void)
{
  _mm512_prefetch_i64scatter_pd (base, idx, 8, _MM_HINT_T0);
  _mm512_mask_prefetch_i64scatter_pd (base, m8, idx, 8, _MM_HINT_ET0);
}