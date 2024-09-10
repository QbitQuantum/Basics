void extern
avx512f_test (void)
{
  res = _mm512_lzcnt_epi32 (s);
  res = _mm512_mask_lzcnt_epi32 (res, 2, s);
  res = _mm512_maskz_lzcnt_epi32 (2, s);
}