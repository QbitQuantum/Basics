 SIMD_INLINE __m256i Average16(const __m256i & s0, const __m256i & s1)
 {
     return _mm256_srli_epi16(_mm256_add_epi16(_mm256_add_epi16(
         _mm256_hadd_epi16(_mm256_unpacklo_epi8(s0, K_ZERO), _mm256_unpackhi_epi8(s0, K_ZERO)),
         _mm256_hadd_epi16(_mm256_unpacklo_epi8(s1, K_ZERO), _mm256_unpackhi_epi8(s1, K_ZERO))), K16_0002), 2); 
 }