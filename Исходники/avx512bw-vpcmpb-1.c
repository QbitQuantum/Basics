void extern
avx512bw_test (void)
{
  mmm = _mm512_cmp_epi8_mask (xq, xq, _MM_CMPINT_GE);
  mmm = _mm512_mask_cmp_epi8_mask (m, xq, xq, _MM_CMPINT_NLE);
  mm = _mm256_cmp_epi8_mask (x, x, _MM_CMPINT_GT);
  mm = _mm256_mask_cmp_epi8_mask (m, x, x, _MM_CMPINT_EQ);
  m = _mm_cmp_epi8_mask (xx, xx, _MM_CMPINT_LT);
  m = _mm_mask_cmp_epi8_mask (m, xx, xx, _MM_CMPINT_LE);
}