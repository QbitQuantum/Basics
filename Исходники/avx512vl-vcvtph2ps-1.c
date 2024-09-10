void extern
avx512bw_test (void)
{
  y = _mm256_mask_cvtph_ps (y, 4, x);
  y = _mm256_maskz_cvtph_ps (6, x);
  yy = _mm_mask_cvtph_ps (yy, 4, xx);
  yy = _mm_maskz_cvtph_ps (6, xx);
}