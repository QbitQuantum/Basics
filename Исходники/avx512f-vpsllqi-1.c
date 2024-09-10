void extern
avx512f_test (void)
{
  x = _mm512_slli_epi64 (x, y);
  x = _mm512_mask_slli_epi64 (x, m, x, y);
  x = _mm512_maskz_slli_epi64 (m, x, y);
}