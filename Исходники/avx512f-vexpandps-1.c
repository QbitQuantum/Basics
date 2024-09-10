void extern
avx512f_test (void)
{
  x = _mm512_mask_expand_ps (x, m, x);
  x = _mm512_maskz_expand_ps (m, x);

  x = _mm512_mask_expandloadu_ps (x, m, p);
  x = _mm512_maskz_expandloadu_ps (m, p);
}