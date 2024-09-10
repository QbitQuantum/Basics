void extern
avx512vl_test (void)
{
  res1 = _mm256_mask_cvtepu16_epi32 (res1, m, s);
  res2 = _mm_mask_cvtepu16_epi32 (res2, m, s);

  res1 = _mm256_maskz_cvtepu16_epi32 (m, s);
  res2 = _mm_maskz_cvtepu16_epi32 (m, s);
}