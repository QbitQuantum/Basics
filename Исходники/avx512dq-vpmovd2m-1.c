void extern
avx512dq_test (void)
{
  m8 = _mm_movepi32_mask (x128);
  m8 = _mm256_movepi32_mask (x256);
  m16 = _mm512_movepi32_mask (x512);
}