void extern
avx512f_test (void)
{
  x1 = _mm512_mask_mov_epi64 (x1, m, x2);
  x1 = _mm512_maskz_mov_epi64 (m, x2);

  x1 = _mm512_load_epi64 (p);
  x1 = _mm512_mask_load_epi64 (x1, m, p);
  x1 = _mm512_maskz_load_epi64 (m, p);

  _mm512_store_epi64 (p, x1);
  _mm512_mask_store_epi64 (p, m, x1);
}