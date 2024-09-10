void extern
avx2_test (void)
{
  x = _mm256_blend_epi32 (x, x, 13);
}