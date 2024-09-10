 SIMD_INLINE __m128i BinomialSum16(const __m128i & ab, const __m128i & cd)
 {
     return _mm_add_epi16(_mm_maddubs_epi16(ab, K8_01_03), _mm_maddubs_epi16(cd, K8_03_01));
 }