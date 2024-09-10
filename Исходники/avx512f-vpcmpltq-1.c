void extern
avx512f_test (void)
{
  m = _mm512_cmplt_epi64_mask (x, x);
  m = _mm512_mask_cmplt_epi64_mask (m, x, x);
}