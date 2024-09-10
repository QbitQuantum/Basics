void extern
avx512f_test (void)
{
  y = _mm512_permutexvar_ps (x, y);
  y = _mm512_mask_permutexvar_ps (y, m, x, y);
  y = _mm512_maskz_permutexvar_ps (m, x, y);
}