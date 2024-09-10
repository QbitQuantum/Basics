void extern
avx512pf_test (void)
{
  _mm512_prefetch_i32scatter_ps (base, idx, 8, _MM_HINT_T1);
  _mm512_mask_prefetch_i32scatter_ps (base, m16, idx, 8, _MM_HINT_ET1);
}