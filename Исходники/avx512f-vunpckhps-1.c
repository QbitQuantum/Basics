void extern
avx512f_test (void)
{
  x = _mm512_unpackhi_ps (y, z);
  x = _mm512_mask_unpackhi_ps (x, m, y, z);
  x = _mm512_maskz_unpackhi_ps (m, y, z);
}