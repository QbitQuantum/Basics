 SIMD_INLINE __m128i Average16(const __m128i & s0, const __m128i & s1)
 {
     return _mm_srli_epi16(_mm_add_epi16(_mm_add_epi16(_mm_maddubs_epi16(s0, K8_01), _mm_maddubs_epi16(s1, K8_01)), K16_0002), 2); 
 }