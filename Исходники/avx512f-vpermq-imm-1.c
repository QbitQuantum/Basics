void extern
avx512f_test (void)
{
  x = _mm512_permutex_epi64 (x, 13);
  x = _mm512_mask_permutex_epi64 (x, m, x, 13);
  x = _mm512_maskz_permutex_epi64 (m, x, 13);
}