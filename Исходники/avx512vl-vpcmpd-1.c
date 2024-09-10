void extern
avx512vl_test (void)
{
  m = _mm256_cmp_epi32_mask (x, x, _MM_CMPINT_EQ);
  m = _mm256_mask_cmp_epi32_mask (m, x, x, _MM_CMPINT_EQ);
  m = _mm_cmp_epi32_mask (xx, xx, _MM_CMPINT_EQ);
  m = _mm_mask_cmp_epi32_mask (m, xx, xx, _MM_CMPINT_EQ);
}