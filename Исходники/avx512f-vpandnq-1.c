void extern
avx512f_test (void)
{
  x = _mm512_andnot_epi64 (x, x);
  x = _mm512_mask_andnot_epi64 (x,m, x, x);
  x = _mm512_maskz_andnot_epi64 (m, x, x);
}