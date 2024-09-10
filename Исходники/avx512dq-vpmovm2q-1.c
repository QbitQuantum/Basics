void extern
avx512dq_test (void)
{
  x128 = _mm_movm_epi64 (m8);
  x256 = _mm256_movm_epi64 (m8);
  x512 = _mm512_movm_epi64 (m8);
}