void extern
avx512vl_test (void)
{
  yy = _mm256_mask_mov_epi64 (yy, m, y2);
  xx = _mm_mask_mov_epi64 (xx, m, x2);

  yy = _mm256_maskz_mov_epi64 (m, y2);
  xx = _mm_maskz_mov_epi64 (m, x2);

  yy = _mm256_load_si256 (p1);
  xx = _mm_load_si128 (p2);

  yy = _mm256_mask_load_epi64 (yy, m, p);
  xx = _mm_mask_load_epi64 (xx, m, p);

  yy = _mm256_maskz_load_epi64 (m, p);
  xx = _mm_maskz_load_epi64 (m, p);

  _mm256_store_epi64 (p, yy);
  _mm_store_epi64 (p, xx);

  _mm256_mask_store_epi64 (p, m, yy);
  _mm_mask_store_epi64 (p, m, xx);
}