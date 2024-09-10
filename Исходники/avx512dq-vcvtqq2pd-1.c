void extern
avx512dq_test (void)
{
  res1 = _mm512_cvtepi64_pd (s1);
  res1 = _mm512_mask_cvtepi64_pd (res1, m, s1);
  res1 = _mm512_maskz_cvtepi64_pd (m, s1);
  res2 = _mm256_cvtepi64_pd (s2);
  res2 = _mm256_mask_cvtepi64_pd (res2, m, s2);
  res2 = _mm256_maskz_cvtepi64_pd (m, s2);
  res3 = _mm_cvtepi64_pd (s3);
  res3 = _mm_mask_cvtepi64_pd (res3, m, s3);
  res3 = _mm_maskz_cvtepi64_pd (m, s3);
  res1 = _mm512_cvt_roundepi64_pd (s1, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  res1 = _mm512_mask_cvt_roundepi64_pd (res1, m, s1, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
  res1 = _mm512_maskz_cvt_roundepi64_pd (m, s1, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}