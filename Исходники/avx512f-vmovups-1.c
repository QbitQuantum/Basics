void extern
avx512f_test (void)
{
  x = _mm512_loadu_ps (p);
  x = _mm512_mask_loadu_ps (x, m, p);
  x = _mm512_maskz_loadu_ps (m, p);

  _mm512_storeu_ps (p, x);
  _mm512_mask_storeu_ps (p, m, x);
}