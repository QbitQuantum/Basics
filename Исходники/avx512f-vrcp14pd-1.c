void extern
avx512f_test (void)
{
  x = _mm512_rcp14_pd (x);
  x = _mm512_mask_rcp14_pd (x, m, x);
  x = _mm512_maskz_rcp14_pd (m, x);
}