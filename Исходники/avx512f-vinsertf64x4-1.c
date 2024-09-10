void extern
avx512f_test (void)
{
  x = _mm512_insertf64x4 (x, y, 1);
  x = _mm512_mask_insertf64x4 (x, 2, x, y, 1);
  x = _mm512_maskz_insertf64x4 (2, x, y, 1);
}