void extern
avx512f_test (void)
{
  m8 = _mm512_test_epi64_mask (x, x);
  m8 = _mm512_mask_test_epi64_mask (3, x, x);
}