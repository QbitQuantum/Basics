void extern
avx512vl_test (void)
{
  x = _mm256_rol_epi64 (x, 11);
  x = _mm256_mask_rol_epi64 (x, m, x, 11);
  x = _mm256_maskz_rol_epi64 (m, x, 11);

  y = _mm_rol_epi64 (y, 12);
  y = _mm_mask_rol_epi64 (y, m, y, 12);
  y = _mm_maskz_rol_epi64 (m, y, 12);
}