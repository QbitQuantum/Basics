void extern
avx512f_test (void)
{
  x = _mm512_shuffle_pd (x, x, 56);
  x = _mm512_mask_shuffle_pd (x, 2, x, x, 56);
  x = _mm512_maskz_shuffle_pd (2, x, x, 56);
}