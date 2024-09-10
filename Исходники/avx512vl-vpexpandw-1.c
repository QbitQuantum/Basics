void extern
avx512vl_test (void)
{
  x1 = _mm256_mask_expand_epi16 (x1, m, x1);
  x2 = _mm_mask_expand_epi16 (x2, m, x2);

  x1 = _mm256_maskz_expand_epi16 (m, x1);
  x2 = _mm_maskz_expand_epi16 (m, x2);

  x1 = _mm256_mask_expandloadu_epi16 (x1, m, p);
  x2 = _mm_mask_expandloadu_epi16 (x2, m, p);

  x1 = _mm256_maskz_expandloadu_epi16 (m, p);
  x2 = _mm_maskz_expandloadu_epi16 (m, p);
}