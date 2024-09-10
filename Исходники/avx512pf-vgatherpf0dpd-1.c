void extern
avx512pf_test (void)
{
  _mm512_mask_prefetch_i32gather_pd (idx, m8, base, 8, _MM_HINT_T0);
}