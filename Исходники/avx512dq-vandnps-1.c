void extern
avx512dq_test (void)
{
  z = _mm512_andnot_ps (z, z);
  z = _mm512_mask_andnot_ps (z, m1, z, z);
  z = _mm512_maskz_andnot_ps (m1, z, z);
  y = _mm256_mask_andnot_ps (y, m2, y, y);
  y = _mm256_maskz_andnot_ps (m2, y, y);
  x = _mm_mask_andnot_ps (x, m2, x, x);
  x = _mm_maskz_andnot_ps (m2, x, x);
}