void extern
avx512bw_test (void)
{
  x3 = _mm512_permutex2var_epi16 (x3, z, x3);
  x3 = _mm512_mask_permutex2var_epi16 (x3, m3, z, x3);
  x3 = _mm512_maskz_permutex2var_epi16 (m3, x3, z, x3);
  x2 = _mm256_permutex2var_epi16 (x2, y, x2);
  x2 = _mm256_mask_permutex2var_epi16 (x2, m2, y, x2);
  x2 = _mm256_maskz_permutex2var_epi16 (m2, x2, y, x2);
  x1 = _mm_permutex2var_epi16 (x1, x, x1);
  x1 = _mm_mask_permutex2var_epi16 (x1, m1, x, x1);
  x1 = _mm_maskz_permutex2var_epi16 (m1, x1, x, x1);
}