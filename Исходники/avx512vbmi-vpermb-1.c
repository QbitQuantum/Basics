void extern
avx512bw_test (void)
{
  x1 = _mm512_permutexvar_epi8 (x1, x1);
  x1 = _mm512_maskz_permutexvar_epi8 (m1, x1, x1);
  x1 = _mm512_mask_permutexvar_epi8 (x1, m1, x1, x1);
  x2 = _mm256_permutexvar_epi8 (x2, x2);
  x2 = _mm256_maskz_permutexvar_epi8 (m2, x2, x2);
  x2 = _mm256_mask_permutexvar_epi8 (x2, m2, x2, x2);
  x3 = _mm_permutexvar_epi8 (x3, x3);
  x3 = _mm_maskz_permutexvar_epi8 (m3, x3, x3);
  x3 = _mm_mask_permutexvar_epi8 (x3, m3, x3, x3);
}