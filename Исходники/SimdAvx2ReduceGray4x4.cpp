 SIMD_INLINE __m256i DivideBy64(__m256i value)
 {
     return _mm256_srli_epi16(_mm256_add_epi16(value, K16_0020), 6);
 }