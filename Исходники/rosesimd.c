__SIMDi _SIMD_abs_epi32(__SIMDi a)
{
#ifdef  USE_SSE
  return _mm_andnot_si128(_mm_set1_epi32(-0), a);
#elif defined USE_AVX
  return _mm256_andnot_si256(_mm256_set1_epi32(-0), a);
#elif defined USE_IBM
  return vec_abs(a);
#endif
}