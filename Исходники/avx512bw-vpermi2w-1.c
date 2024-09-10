void extern
avx512bw_test (void)
{
  x3 = _mm512_mask2_permutex2var_epi16 (x3, z, m3, x3);
  x2 = _mm256_mask2_permutex2var_epi16 (x2, y, m2, x2);
  x1 = _mm_mask2_permutex2var_epi16 (x1, x, m1, x1);
}