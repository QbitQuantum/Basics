void extern
avx512f_test (void)
{
  m = _mm512_cmplt_epu64_mask (x, x);
}