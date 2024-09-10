void extern
avx512vl_test (void)
{
  yy = _mm256_mask_mov_ps (yy, m, y2);
  xx = _mm_mask_mov_ps (xx, m, x2);

  yy = _mm256_maskz_mov_ps (m, y2);
  xx = _mm_maskz_mov_ps (m, x2);

  yy = _mm256_mask_load_ps (yy, m, p);
  xx = _mm_mask_load_ps (xx, m, p);

  yy = _mm256_maskz_load_ps (m, p);
  xx = _mm_maskz_load_ps (m, p);

  _mm256_mask_store_ps (p, m, yy);
  _mm_mask_store_ps (p, m, xx);
}