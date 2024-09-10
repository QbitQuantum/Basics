void extern
avx512vl_test (void)
{
  x = _mm512_sad_epu8 (x, x);
}