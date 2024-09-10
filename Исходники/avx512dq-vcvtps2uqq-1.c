void extern
avx512dq_test (void)
{
  x1 = _mm512_cvtps_epu64 (z1);
  x1 = _mm512_mask_cvtps_epu64 (x1, m, z1);
  x1 = _mm512_maskz_cvtps_epu64 (m, z1);
  x2 = _mm256_cvtps_epu64 (z2);
  x2 = _mm256_mask_cvtps_epu64 (x2, m, z2);
  x2 = _mm256_maskz_cvtps_epu64 (m, z2);
  x3 = _mm_cvtps_epu64 (z2);
  x3 = _mm_mask_cvtps_epu64 (x3, m, z2);
  x3 = _mm_maskz_cvtps_epu64 (m, z2);
  x1 = _mm512_cvt_roundps_epu64 (z1, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  x1 = _mm512_mask_cvt_roundps_epu64 (x1, m, z1, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
  x1 = _mm512_maskz_cvt_roundps_epu64 (m, z1, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}