void extern
avx512f_test (void)
{
  x1 = _mm512_mask_mov_pd (x1, m, x2);
  x1 = _mm512_maskz_mov_pd (m, x2);

  x1 = _mm512_load_pd (p);
  x1 = _mm512_mask_load_pd (x1, m, p);
  x1 = _mm512_maskz_load_pd (m, p);

  _mm512_store_pd (p, x1);
  _mm512_mask_store_pd (p, m, x1);
}