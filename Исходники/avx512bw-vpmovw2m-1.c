void extern
avx512bw_test (void)
{
  m8 = _mm_movepi16_mask (x128);
  m16 = _mm256_movepi16_mask (x256);
  m32 = _mm512_movepi16_mask (x512);
}