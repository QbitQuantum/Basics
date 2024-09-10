void extern
avx512f_test (void)
{
  x = _mm512_broadcastd_epi32 (y);
  x = _mm512_mask_broadcastd_epi32 (x, m, y);
  x = _mm512_maskz_broadcastd_epi32 (m, y);

  x = _mm512_set1_epi32 (z);
  x = _mm512_mask_set1_epi32 (x, m, z);
  x = _mm512_maskz_set1_epi32 (m, z);
}