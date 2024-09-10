void extern
avx512f_test (void)
{
  x = _mm512_rolv_epi64 (x, x);
  x = _mm512_mask_rolv_epi64 (x, m, x, x);
  x = _mm512_maskz_rolv_epi64 (m, x, x);
}