void extern
avx512bw_test (void)
{
  z = _mm512_alignr_epi8 (z, z, 10);
  z = _mm512_mask_alignr_epi8 (z, m1, z, z, 10);
  z = _mm512_maskz_alignr_epi8 (m1, z, z, 10);
  y = _mm256_mask_alignr_epi8 (y, m2, y, y, 10);
  y = _mm256_maskz_alignr_epi8 (m2, y, y, 10);
  x = _mm_mask_alignr_epi8 (x, m3, x, x, 10);
  x = _mm_maskz_alignr_epi8 (m3, x, x, 10);
}