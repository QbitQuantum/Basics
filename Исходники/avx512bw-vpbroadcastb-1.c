void extern
avx512bw_test (void)
{
  x = _mm512_broadcastb_epi8 (z);
  x = _mm512_mask_broadcastb_epi8 (x, mx, z);
  x = _mm512_maskz_broadcastb_epi8 (mx, z);
  y = _mm256_mask_broadcastb_epi8 (y, my, z);
  y = _mm256_maskz_broadcastb_epi8 (my, z);
  z = _mm_mask_broadcastb_epi8 (z, mz, z);
  z = _mm_maskz_broadcastb_epi8 (mz, z);

  x = _mm512_set1_epi8 (w);
  x = _mm512_mask_set1_epi8 (x, mx, w);
  x = _mm512_maskz_set1_epi8 (mx, w);
  y = _mm256_mask_set1_epi8 (y, my, w);
  y = _mm256_maskz_set1_epi8 (my, w);
  z = _mm_mask_set1_epi8 (z, mz, w);
  z = _mm_maskz_set1_epi8 (mz, w);
}