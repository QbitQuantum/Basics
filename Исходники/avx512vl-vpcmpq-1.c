void extern
avx512bw_test (void)
{
  m = _mm256_cmp_epi64_mask (x, x, _MM_CMPINT_UNUSED);
  m = _mm256_mask_cmp_epi64_mask (m, x, x, _MM_CMPINT_NE);
  m = _mm_cmp_epi64_mask (xx, xx, _MM_CMPINT_NLT);
  m = _mm_mask_cmp_epi64_mask (m, xx, xx, _MM_CMPINT_GE);
}