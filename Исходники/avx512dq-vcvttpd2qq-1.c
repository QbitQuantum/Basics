void extern
avx512dq_test (void)
{
  res1 = _mm512_cvttpd_epi64 (s1);
  res2 = _mm256_cvttpd_epi64 (s2);
  res3 = _mm_cvttpd_epi64 (s3);

  res1 = _mm512_mask_cvttpd_epi64 (res1, m, s1);
  res2 = _mm256_mask_cvttpd_epi64 (res2, m, s2);
  res3 = _mm_mask_cvttpd_epi64 (res3, m, s3);

  res1 = _mm512_maskz_cvttpd_epi64 (m, s1);
  res2 = _mm256_maskz_cvttpd_epi64 (m, s2);
  res3 = _mm_maskz_cvttpd_epi64 (m, s3);

  res1 = _mm512_cvtt_roundpd_epi64 (s1, _MM_FROUND_NO_EXC);
  res1 = _mm512_mask_cvtt_roundpd_epi64 (res1, m, s1, _MM_FROUND_NO_EXC);
  res1 = _mm512_maskz_cvtt_roundpd_epi64 (m, s1, _MM_FROUND_NO_EXC);
}