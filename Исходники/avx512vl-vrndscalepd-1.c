void extern
avx512vl_test (void)
{
  x1 = _mm256_roundscale_pd (x1, 0x42);
  x1 = _mm256_ceil_pd (x1);
  x1 = _mm256_floor_pd (x1);
  x1 = _mm256_mask_roundscale_pd (x1, 2, x1, 0x42);
  x1 = _mm256_maskz_roundscale_pd (2, x1, 0x42);
  x2 = _mm_roundscale_pd (x2, 0x42);
  x2 = _mm_ceil_pd (x2);
  x2 = _mm_floor_pd (x2);
  x2 = _mm_mask_roundscale_pd (x2, 2, x2, 0x42);
  x2 = _mm_maskz_roundscale_pd (2, x2, 0x42);
}