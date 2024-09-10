void extern
avx512dq_test (void)
{
  res1 = _mm512_cvtepu64_ps (s1);
  res1 = _mm512_mask_cvtepu64_ps (res1, m, s1);
  res1 = _mm512_maskz_cvtepu64_ps (m, s1);
  res2 = _mm256_cvtepu64_ps (s2);
  res2 = _mm256_mask_cvtepu64_ps (res2, m, s2);
  res2 = _mm256_maskz_cvtepu64_ps (m, s2);
  res2 = _mm_cvtepu64_ps (s3);
  res2 = _mm_mask_cvtepu64_ps (res2, m, s3);
  res2 = _mm_maskz_cvtepu64_ps (m, s3);
  res1 = _mm512_cvt_roundepu64_ps (s1, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  res1 = _mm512_mask_cvt_roundepu64_ps (res1, m, s1, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
  res1 = _mm512_maskz_cvt_roundepu64_ps (m, s1, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}