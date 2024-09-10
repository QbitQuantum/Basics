void extern
avx512f_test (void)
{
  x = _mm512_maskz_inserti32x4 (6, x, y, 1);
  x = _mm512_mask_inserti32x4 (a, 6, x, y, 1);
  x = _mm512_inserti32x4 (x, y, 1);
}