void extern
avx512vl_test (void)
{
  xx = _mm256_mask_abs_epi32 (xx, 2,xx);
  xx = _mm256_maskz_abs_epi32 (2, xx);
  x2 = _mm_mask_abs_epi32 (x2, 2, x2);
  x2 = _mm_maskz_abs_epi32 (2, x2);
}