void extern
avx512vl_test (void)
{
  x256 = _mm256_mask_sll_epi64 (x256, m256, x256, x128);
  x256 = _mm256_maskz_sll_epi64 (m256, x256, x128);
  x128 = _mm_mask_sll_epi64 (x128, m128, x128, x128);
  x128 = _mm_maskz_sll_epi64 (m128, x128, x128);
}