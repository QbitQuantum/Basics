void extern
avx512f_test (void)
{
  x = _mm512_unpacklo_pd (y, z);
  x = _mm512_mask_unpacklo_pd (x, m, y, z);
  x = _mm512_maskz_unpacklo_pd (m, y, z);
}