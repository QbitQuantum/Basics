void extern
avx2_test (void)
{
  x = _mm_i32gather_ps (base, idx, 1);
}