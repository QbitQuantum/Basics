void extern
avx512dq_test (void)
{
  x = _mm256_inserti64x2 (x, y, 1);
  x = _mm256_mask_inserti64x2 (x, 2, x, y, 1);
  x = _mm256_maskz_inserti64x2 (2, x, y, 1);
  z = _mm512_inserti64x2 (z, y, 0);
  z = _mm512_mask_inserti64x2 (z, 2, z, y, 0);
  z = _mm512_maskz_inserti64x2 (2, z, y, 0);
}