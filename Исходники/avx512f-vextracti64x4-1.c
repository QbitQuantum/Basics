void extern
avx512f_test (void)
{
  y = _mm512_extracti64x4_epi64 (x, 1);
  y = _mm512_mask_extracti64x4_epi64 (y, 2, x, 1);
  y = _mm512_maskz_extracti64x4_epi64 (2, x, 1);
}