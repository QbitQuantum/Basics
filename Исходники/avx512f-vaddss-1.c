void extern
avx512f_test (void)
{
  x1 = _mm_add_round_ss (x1, x2, _MM_FROUND_TO_NEAREST_INT);
}