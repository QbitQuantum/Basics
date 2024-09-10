void extern
avx512bw_test (void)
{
  z = _mm512_avg_epu16 (z, z);
  z = _mm512_mask_avg_epu16 (z, m1, z, z);
  z = _mm512_maskz_avg_epu16 (m1, z, z);
  y = _mm256_mask_avg_epu16 (y, m2, y, y);
  y = _mm256_maskz_avg_epu16 (m2, y, y);
  x = _mm_mask_avg_epu16 (x, m3, x, x);
  x = _mm_maskz_avg_epu16 (m3, x, x);
}