void extern
avx512f_test (void)
{
  x = _mm512_mask2_permutex2var_ps (x, y, m, x);
}