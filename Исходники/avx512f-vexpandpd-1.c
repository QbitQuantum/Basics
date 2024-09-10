void extern
avx512f_test (void)
{
  x = _mm512_mask_expand_pd (x, m, x);
  x = _mm512_maskz_expand_pd (m, x);

  x = _mm512_mask_expandloadu_pd (x, m, p);
  x = _mm512_maskz_expandloadu_pd (m, p);
}