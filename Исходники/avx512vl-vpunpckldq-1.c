void extern
avx512bw_test (void)
{
  x = _mm256_mask_unpacklo_epi32 (x, m, y, z);
  x = _mm256_maskz_unpacklo_epi32 (m, y, z);
  a = _mm_mask_unpacklo_epi32 (a, m, b, c);
  a = _mm_maskz_unpacklo_epi32 (m, b, c);
}