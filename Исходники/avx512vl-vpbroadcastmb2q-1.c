void extern
avx512vl_test (void)
{
  x128 = _mm_broadcastmb_epi64 (m8);
  x256 = _mm256_broadcastmb_epi64 (m8);
}