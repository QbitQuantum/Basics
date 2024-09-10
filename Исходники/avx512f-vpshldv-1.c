void extern
avx512f_test (void)
{
  x = _mm512_shldv_epi16 (x, y, z);
  x = _mm512_mask_shldv_epi16 (x, m32, y, z);
  x = _mm512_maskz_shldv_epi16 (m32, x, y, z);

  x = _mm512_shldv_epi32 (x, y, z);
  x = _mm512_mask_shldv_epi32 (x, m16, y, z);
  x = _mm512_maskz_shldv_epi32 (m16, x, y, z);

  x = _mm512_shldv_epi64 (x, y, z);
  x = _mm512_mask_shldv_epi64 (x, m8, y, z);
  x = _mm512_maskz_shldv_epi64 (m8, x, y, z);
}