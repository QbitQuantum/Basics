void extern
avx512f_test (void)
{
  x = _mm512_mask_blend_pd (m, x, x);
}