void extern
avx512f_test (void)
{
  x1 = _mm_roundscale_ss (x1, x2, 0x42);
  x1 = _mm_roundscale_round_ss (x1, x2, 0x42, _MM_FROUND_NO_EXC);
}