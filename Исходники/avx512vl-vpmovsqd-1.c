void extern
avx512vl_test (void)
{
  z = _mm_cvtsepi64_epi32 (x);
  z = _mm_mask_cvtsepi64_epi32 (z, m, x);
  z = _mm_maskz_cvtsepi64_epi32 (m, x);
  z = _mm256_cvtsepi64_epi32 (y);
  z = _mm256_mask_cvtsepi64_epi32 (z, m, y);
  z = _mm256_maskz_cvtsepi64_epi32 (m, y);
}