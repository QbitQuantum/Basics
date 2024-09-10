void extern
avx512vl_test (void)
{
  x = _mm256_shuffle_f32x4 (x, x, 2);
  x = _mm256_mask_shuffle_f32x4 (x, m, x, x, 2);
  x = _mm256_maskz_shuffle_f32x4 (m, x, x, 2);
}