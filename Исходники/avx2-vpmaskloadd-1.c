void extern
avx2_test (void)
{
  x = _mm_maskload_epi32 (y, x);
}