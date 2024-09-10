void extern
avx512f_test (void)
{
  x = _mm512_abs_epi32 (x);
  x = _mm512_maskz_abs_epi32 (7, x);
  x = _mm512_mask_abs_epi32 (x, 6, x);
}