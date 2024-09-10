void extern
avx512f_test (void)
{
  x = _mm512_rcp14_ps (x);
  x = _mm512_mask_rcp14_ps (x, m, x);
  x = _mm512_maskz_rcp14_ps (m, x);
}