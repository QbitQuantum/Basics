void extern
avx512vl_test (void)
{
  xx = _mm256_getexp_ps (xx);
  xx = _mm256_mask_getexp_ps (xx, m8, xx);
  xx = _mm256_maskz_getexp_ps (m8, xx);
  x2 = _mm_getexp_ps (x2);
  x2 = _mm_mask_getexp_ps (x2, m8, x2);
  x2 = _mm_maskz_getexp_ps (m8, x2);
}