void extern
avx512vl_test (void)
{
  x = _mm256_shuffle_f64x2 (x, x, 2);
  x = _mm256_mask_shuffle_f64x2 (x, m, x, x, 2);
  x = _mm256_maskz_shuffle_f64x2 (m, x, x, 2);
}