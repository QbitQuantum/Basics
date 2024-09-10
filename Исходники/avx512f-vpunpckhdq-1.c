void extern
avx512f_test (void)
{
  x = _mm512_unpackhi_epi32 (y, z);
  x = _mm512_mask_unpackhi_epi32 (x, m, y, z);
  x = _mm512_maskz_unpackhi_epi32 (m, y, z);
}