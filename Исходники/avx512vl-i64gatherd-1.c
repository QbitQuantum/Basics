void extern
avx512vl_test (void)
{
  x = _mm256_mmask_i64gather_epi32 (x, 0xFF, idx1, base, 8);
  x = _mm256_mmask_i64gather_epi32 (x, m8, idx1, base, 8);
  x = _mm_mmask_i64gather_epi32 (x, 0xFF, idx2, base, 8);
  x = _mm_mmask_i64gather_epi32 (x, m8, idx2, base, 8);
}