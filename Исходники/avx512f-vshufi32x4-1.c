void extern
avx512f_test (void)
{
  x = _mm512_shuffle_i32x4 (x, x, 56);
  x = _mm512_mask_shuffle_i32x4 (x, 8, x, x, 56);
  x = _mm512_maskz_shuffle_i32x4 (8, x, x, 56);
}