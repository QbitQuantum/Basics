void extern
avx512f_test (void)
{
  x = _mm512_broadcast_i64x4 (y);
  x = _mm512_mask_broadcast_i64x4 (x, m, y);
  x = _mm512_maskz_broadcast_i64x4 (m, y);
}