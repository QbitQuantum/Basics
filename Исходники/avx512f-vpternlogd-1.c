void extern
avx512f_test (void)
{
  x = _mm512_ternarylogic_epi32 (x, y, z, 0xF0);
  x = _mm512_mask_ternarylogic_epi32 (x, m, y, z, 0xF0);
  x = _mm512_maskz_ternarylogic_epi32 (m, x, y, z, 0xF0);
}