void extern
avx512bw_test (void)
{
  m8 = _mm_cmpge_epi16_mask (x128, x128);
  m16 = _mm256_cmpge_epi16_mask (x256, x256);
  m32 = _mm512_cmpge_epi16_mask (x512, x512);
  m8 = _mm_mask_cmpge_epi16_mask (3, x128, x128);
  m16 = _mm256_mask_cmpge_epi16_mask (3, x256, x256);
  m32 = _mm512_mask_cmpge_epi16_mask (3, x512, x512);
}