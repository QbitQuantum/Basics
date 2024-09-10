void extern
avx512bw_test (void)
{
  x = _mm512_min_epi16 (x, x);
  x = _mm512_mask_min_epi16 (x, mx, x, x);
  x = _mm512_maskz_min_epi16 (mx, x, x);
  y = _mm256_mask_min_epi16 (y, my, y, y);
  y = _mm256_maskz_min_epi16 (my, y, y);
  z = _mm_mask_min_epi16 (z, mz, z, z);
  z = _mm_maskz_min_epi16 (mz, z, z);
}