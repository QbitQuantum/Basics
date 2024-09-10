void extern
avx512bw_test (void)
{
  x = _mm512_max_epi8 (x, x);
  x = _mm512_mask_max_epi8 (x, mx, x, x);
  x = _mm512_maskz_max_epi8 (mx, x, x);
  y = _mm256_mask_max_epi8 (y, my, y, y);
  y = _mm256_maskz_max_epi8 (my, y, y);
  z = _mm_mask_max_epi8 (z, mz, z, z);
  z = _mm_maskz_max_epi8 (mz, z, z);
}