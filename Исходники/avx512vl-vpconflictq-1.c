void extern
avx512vl_test (void)
{
  res = _mm256_conflict_epi64 (s);
  res = _mm256_mask_conflict_epi64 (res, 2, s);
  res = _mm256_maskz_conflict_epi64 (2, s);
  res2 = _mm_conflict_epi64 (s2);
  res2 = _mm_mask_conflict_epi64 (res2, 2, s2);
  res2 = _mm_maskz_conflict_epi64 (2, s2);
}