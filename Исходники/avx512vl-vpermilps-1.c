void extern
avx512vl_test (void)
{
  y = _mm256_mask_permutevar_ps (y, m, y, c);
  y = _mm256_maskz_permutevar_ps (m, y, c);
  x = _mm_mask_permutevar_ps (x, m, x, k);
  x = _mm_maskz_permutevar_ps (m, x, k);
}