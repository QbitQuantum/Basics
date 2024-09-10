void extern
avx512f_test (void)
{
  x = _mm512_permutex_pd (x, 13);
  x = _mm512_mask_permutex_pd (x, m, x, 13);
  x = _mm512_maskz_permutex_pd (m, x, 13);
}