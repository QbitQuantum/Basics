void extern
avx512bw_test (void)
{
  x128 = _mm_movm_epi8 (m16);
  x256 = _mm256_movm_epi8 (m32);
  x512 = _mm512_movm_epi8 (m64);
}