void extern
avx512f_test (void)
{
  x = _mm512_broadcastss_ps (y);
  x = _mm512_mask_broadcastss_ps (x, m, y);
  x = _mm512_maskz_broadcastss_ps (m, y);
}