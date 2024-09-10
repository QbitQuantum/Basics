void extern
avx512dq_test (void)
{
  y = _mm512_extractf64x2_pd (x1, 3);
  y = _mm512_mask_extractf64x2_pd (y, 2, x1, 3);
  y = _mm512_maskz_extractf64x2_pd (2, x1, 3);
  y = _mm256_extractf64x2_pd (x2, 1);
  y = _mm256_mask_extractf64x2_pd (y, 2, x2, 1);
  y = _mm256_maskz_extractf64x2_pd (2, x2, 1);
}