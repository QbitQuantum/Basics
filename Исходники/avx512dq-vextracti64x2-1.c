void extern
avx512dq_test (void)
{
  y = _mm512_extracti64x2_epi64 (x1, 3);
  y = _mm512_mask_extracti64x2_epi64 (y, 2, x1, 3);
  y = _mm512_maskz_extracti64x2_epi64 (2, x1, 3);
  y = _mm256_extracti64x2_epi64 (x2, 1);
  y = _mm256_mask_extracti64x2_epi64 (y, 2, x2, 1);
  y = _mm256_maskz_extracti64x2_epi64 (2, x2, 1);
}