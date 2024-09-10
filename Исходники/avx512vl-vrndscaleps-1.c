void extern
avx512vl_test (void)
{
  x1 = _mm256_roundscale_ps (x1, 0x42);
  x1 = _mm256_ceil_ps (x1);
  x1 = _mm256_floor_ps (x1);
  x1 = _mm256_mask_roundscale_ps (x1, 2, x1, 0x42);
  x1 = _mm256_maskz_roundscale_ps (2, x1, 0x42);
  x2 = _mm_roundscale_ps (x2, 0x42);
  x2 = _mm_ceil_ps (x2);
  x2 = _mm_floor_ps (x2);
  x2 = _mm_mask_roundscale_ps (x2, 2, x2, 0x42);
  x2 = _mm_maskz_roundscale_ps (2, x2, 0x42);
}