void extern
avx512f_test (void)
{
  x = _mm512_shuffle_i64x2 (x, x, 56);
  x = _mm512_mask_shuffle_i64x2 (x, 3, x, x, 56);
  x = _mm512_maskz_shuffle_i64x2 (2, x, x, 56);
}