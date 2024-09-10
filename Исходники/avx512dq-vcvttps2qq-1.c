void extern
avx512dq_test (void)
{
  x1 = _mm512_cvttps_epi64 (z1);
  x1 = _mm512_mask_cvttps_epi64 (x1, m, z1);
  x1 = _mm512_maskz_cvttps_epi64 (m, z1);
  x2 = _mm256_cvttps_epi64 (z2);
  x2 = _mm256_mask_cvttps_epi64 (x2, m, z2);
  x2 = _mm256_maskz_cvttps_epi64 (m, z2);
  x3 = _mm_cvttps_epi64 (z2);
  x3 = _mm_mask_cvttps_epi64 (x3, m, z2);
  x3 = _mm_maskz_cvttps_epi64 (m, z2);
  x1 = _mm512_cvtt_roundps_epi64 (z1, _MM_FROUND_NO_EXC);
  x1 = _mm512_mask_cvtt_roundps_epi64 (x1, m, z1, _MM_FROUND_NO_EXC);
  x1 = _mm512_maskz_cvtt_roundps_epi64 (m, z1, _MM_FROUND_NO_EXC);
}