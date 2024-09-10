void extern
avx512bw_test (void)
{
  mmm = _mm512_cmp_epu8_mask (xq, xq, _MM_CMPINT_EQ);
  mmm = _mm512_mask_cmp_epu8_mask (m, xq, xq, _MM_CMPINT_LT);
  mm = _mm256_cmp_epu8_mask (x, x, _MM_CMPINT_LE);
  mm = _mm256_mask_cmp_epu8_mask (m, x, x, _MM_CMPINT_UNUSED);
  m = _mm_cmp_epu8_mask (xx, xx, _MM_CMPINT_NE);
  m = _mm_mask_cmp_epu8_mask (m, xx, xx, _MM_CMPINT_NLT);
}