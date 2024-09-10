void extern
avx512bw_test (void)
{
  x = _mm512_packus_epi32 (x, x);
  x = _mm512_mask_packus_epi32 (x, mx, x, x);
  x = _mm512_maskz_packus_epi32 (mx, x, x);
  y = _mm256_mask_packus_epi32 (y, my, y, y);
  y = _mm256_maskz_packus_epi32 (my, y, y);
  z = _mm_mask_packus_epi32 (z, mz, z, z);
  z = _mm_maskz_packus_epi32 (mz, z, z);
}