void extern
avx512f_test (void)
{
  x = _mm512_permutex2var_epi64 (x, x, x);
  x = _mm512_mask_permutex2var_epi64 (x, m, x, x);
  x = _mm512_maskz_permutex2var_epi64 (m, x, x, x);
}