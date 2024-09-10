void extern
avx512vl_test (void)
{
  x1 = _mm256_mmask_i64gather_epi64 (x1, 0xFF, idx1, base, 8);
  x1 = _mm256_mmask_i64gather_epi64 (x1, m8, idx1, base, 8);
  x2 = _mm_mmask_i64gather_epi64 (x2, 0xFF, idx2, base, 8);
  x2 = _mm_mmask_i64gather_epi64 (x2, m8, idx2, base, 8);
}