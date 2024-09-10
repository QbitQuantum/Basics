void extern
avx512f_test (void)
{
  x = _mm512_unpackhi_pd (y, z);
  x = _mm512_mask_unpackhi_pd (x, m, y, z);
  x = _mm512_maskz_unpackhi_pd (m, y, z);
}