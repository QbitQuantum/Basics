void extern
avx512bw_test (void)
{
  x512 = _mm512_sub_epi8 (x512, x512);
  x512 = _mm512_mask_sub_epi8 (x512, m512, x512, x512);
  x512 = _mm512_maskz_sub_epi8 (m512, x512, x512);
  x256 = _mm256_mask_sub_epi8 (x256, m256, x256, x256);
  x256 = _mm256_maskz_sub_epi8 (m256, x256, x256);
  x128 = _mm_mask_sub_epi8 (x128, m128, x128, x128);
  x128 = _mm_maskz_sub_epi8 (m128, x128, x128);
}