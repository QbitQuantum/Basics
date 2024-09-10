void extern
avx2_test (void)
{
  x = _mm_blend_epi32 (x, y, 13);
}