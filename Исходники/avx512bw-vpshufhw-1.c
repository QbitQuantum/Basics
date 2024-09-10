void extern
avx512bw_test (void)
{
  z = _mm512_shufflehi_epi16 (z, _MM_PERM_AADB);
  z = _mm512_mask_shufflehi_epi16 (z, m1, z, _MM_PERM_AADB);
  z = _mm512_maskz_shufflehi_epi16 (m1, z, _MM_PERM_AADB);
  y = _mm256_mask_shufflehi_epi16 (y, m2, y, _MM_PERM_AADB);
  y = _mm256_maskz_shufflehi_epi16 (m2, y, _MM_PERM_AADB);
  x = _mm_mask_shufflehi_epi16 (x, m3, x, _MM_PERM_AADB);
  x = _mm_maskz_shufflehi_epi16 (m3, x, _MM_PERM_AADB);
}