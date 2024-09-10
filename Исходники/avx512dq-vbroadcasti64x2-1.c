void extern
avx512dq_test (void)
{
  x = _mm512_broadcast_i64x2 (z);
  x = _mm512_mask_broadcast_i64x2 (x, m, z);
  x = _mm512_maskz_broadcast_i64x2 (m, z);
  y = _mm256_broadcast_i64x2 (z);
  y = _mm256_mask_broadcast_i64x2 (y, m, z);
  y = _mm256_maskz_broadcast_i64x2 (m, z);
}