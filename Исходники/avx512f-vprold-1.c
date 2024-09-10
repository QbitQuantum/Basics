void extern
avx512f_test (void)
{
  x = _mm512_rol_epi32 (x, 12);
  x = _mm512_mask_rol_epi32 (x, m, x, 12);
  x = _mm512_maskz_rol_epi32 (m, x, 12);
}