void extern
avx512f_test (void)
{
  x = _mm512_permute_pd (x, 13);
  x = _mm512_mask_permute_pd (x, m, x, 13);
  x = _mm512_maskz_permute_pd (m, x, 13);
}