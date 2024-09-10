void extern
avx512f_test (void)
{
  m = _mm512_cmp_epi64_mask (x, x, _MM_CMPINT_NE);
  m = _mm512_mask_cmp_epi64_mask (m, x, x, _MM_CMPINT_NLT);
}