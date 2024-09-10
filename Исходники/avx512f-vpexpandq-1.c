void extern
avx512f_test (void)
{
  x = _mm512_mask_expand_epi64 (x, m, x);
  x = _mm512_maskz_expand_epi64 (m, x);

  x = _mm512_mask_expandloadu_epi64 (x, m, p);
  x = _mm512_maskz_expandloadu_epi64 (m, p);
}