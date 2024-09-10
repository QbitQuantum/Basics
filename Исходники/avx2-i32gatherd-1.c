void extern
avx2_test (void)
{
  x = _mm_i32gather_epi32 (base, idx, 1);
}