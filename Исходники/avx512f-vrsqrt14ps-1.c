void extern
avx512f_test (void)
{
  x = _mm512_rsqrt14_ps (x);
  x = _mm512_mask_rsqrt14_ps (x, m, x);
  x = _mm512_maskz_rsqrt14_ps (m, x);
}