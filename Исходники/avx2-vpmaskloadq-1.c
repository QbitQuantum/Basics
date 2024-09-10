void extern
avx2_test (void)
{
  x = _mm_maskload_epi64 (y, x);
}