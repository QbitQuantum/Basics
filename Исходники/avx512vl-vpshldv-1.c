void extern
avx512f_test (void)
{
  x = _mm256_shldv_epi16 (x, y, z);
  x = _mm256_mask_shldv_epi16 (x, m, y, z);
  x = _mm256_maskz_shldv_epi16 (m, x, y, z);

  x = _mm256_shldv_epi32 (x, y, z);
  x = _mm256_mask_shldv_epi32 (x, m, y, z);
  x = _mm256_maskz_shldv_epi32 (m, x, y, z);

  x = _mm256_shldv_epi64 (x, y, z);
  x = _mm256_mask_shldv_epi64 (x, m, y, z);
  x = _mm256_maskz_shldv_epi64 (m, x, y, z);

  x_ = _mm_shldv_epi16 (x_, y_, z_);
  x_ = _mm_mask_shldv_epi16 (x_, m, y_, z_);
  x_ = _mm_maskz_shldv_epi16 (m, x_, y_, z_);

  x_ = _mm_shldv_epi32 (x_, y_, z_);
  x_ = _mm_mask_shldv_epi32 (x_, m, y_, z_);
  x_ = _mm_maskz_shldv_epi32 (m, x_, y_, z_);

  x_ = _mm_shldv_epi64 (x_, y_, z_);
  x_ = _mm_mask_shldv_epi64 (x_, m, y_, z_);
  x_ = _mm_maskz_shldv_epi64 (m, x_, y_, z_);
}