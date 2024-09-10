void extern
avx512f_test (void)
{
  x = _mm512_permutexvar_epi32 (x, x);
  x = _mm512_maskz_permutexvar_epi32 (m, x, x);
  x = _mm512_mask_permutexvar_epi32 (x, m, x, x);
}