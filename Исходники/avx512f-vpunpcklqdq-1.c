void extern
avx512f_test (void)
{
  x = _mm512_unpacklo_epi64 (y, z);
  x = _mm512_mask_unpacklo_epi64 (x, m, y, z);
  x = _mm512_maskz_unpacklo_epi64 (m, y, z);
}