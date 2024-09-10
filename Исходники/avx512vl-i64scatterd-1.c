void extern
avx512vl_test (void)
{
  _mm256_i64scatter_epi32 (addr, idx1, src, 8);
  _mm256_mask_i64scatter_epi32 (addr, m8, idx1, src, 8);

  _mm_i64scatter_epi32 (addr, idx2, src, 8);
  _mm_mask_i64scatter_epi32 (addr, m8, idx2, src, 8);
}