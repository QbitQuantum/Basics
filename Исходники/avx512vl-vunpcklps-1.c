void extern
avx512vl_test (void)
{
  x = _mm256_unpacklo_ps (y, z);
  x = _mm256_mask_unpacklo_ps (x, 2, y, z);
  x = _mm256_maskz_unpacklo_ps (2, y, z);
  xx = _mm_unpacklo_ps (yy, zz);
  xx = _mm_mask_unpacklo_ps (xx, 2, yy, zz);
  xx = _mm_maskz_unpacklo_ps (2, yy, zz);
}