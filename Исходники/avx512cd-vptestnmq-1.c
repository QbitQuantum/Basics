void extern
avx512cd_test (void)
{
  m8 = _mm512_testn_epi64_mask (x, x);
  m8 = _mm512_mask_testn_epi64_mask (3, x, x);
}