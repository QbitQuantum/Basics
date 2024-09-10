void extern
avx512dq_test (void)
{
  x = _mm512_broadcast_f32x8 (y);
  x = _mm512_mask_broadcast_f32x8 (x, m, y);
  x = _mm512_maskz_broadcast_f32x8 (m, y);
}