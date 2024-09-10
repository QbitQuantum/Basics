void extern
avx512bw_test (void)
{
  x = _mm512_broadcastw_epi16 (z);
  x = _mm512_mask_broadcastw_epi16 (x, mx, z);
  x = _mm512_maskz_broadcastw_epi16 (mx, z);
  y = _mm256_mask_broadcastw_epi16 (y, my, z);
  y = _mm256_maskz_broadcastw_epi16 (my, z);
  z = _mm_mask_broadcastw_epi16 (z, mz, z);
  z = _mm_maskz_broadcastw_epi16 (mz, z);

  x = _mm512_set1_epi16 (w);
  x = _mm512_mask_set1_epi16 (x, mx, w);
  x = _mm512_maskz_set1_epi16 (mx, w);
  y = _mm256_mask_set1_epi16 (y, my, w);
  y = _mm256_maskz_set1_epi16 (my, w);
  z = _mm_mask_set1_epi16 (z, mz, w);
  z = _mm_maskz_set1_epi16 (mz, w);
}