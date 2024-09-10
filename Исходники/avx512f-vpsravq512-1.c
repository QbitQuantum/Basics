void extern
avx512f_test (void)
{
  x = _mm512_srav_epi64 (x, x);
}