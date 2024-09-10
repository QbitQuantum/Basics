void extern
avx512f_test (void)
{
  x = _mm512_sra_epi64 (x, y);
  x = _mm512_mask_sra_epi64 (x, m, x, y);
  x = _mm512_maskz_sra_epi64 (m, x, y);
}