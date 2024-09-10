void extern
avx512bw_test (void)
{
  m16 = _mm_cmple_epi8_mask (x128, x128);
  m32 = _mm256_cmple_epi8_mask (x256, x256);
  m64 = _mm512_cmple_epi8_mask (x512, x512);
  m16 = _mm_mask_cmple_epi8_mask (3, x128, x128);
  m32 = _mm256_mask_cmple_epi8_mask (3, x256, x256);
  m64 = _mm512_mask_cmple_epi8_mask (3, x512, x512);
}