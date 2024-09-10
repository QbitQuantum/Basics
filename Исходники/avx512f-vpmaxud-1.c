void extern
avx512f_test (void)
{
  x = _mm512_max_epu32 (x, x);
  x = _mm512_mask_max_epu32 (x, m, x, x);
  x = _mm512_maskz_max_epu32 (m, x, x);
}