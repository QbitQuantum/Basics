void extern
avx512f_test (void)
{
  x = _mm512_permutevar_pd (x, c);
  x = _mm512_mask_permutevar_pd (x, m, x, c);
  x = _mm512_maskz_permutevar_pd (m, x, c);
}