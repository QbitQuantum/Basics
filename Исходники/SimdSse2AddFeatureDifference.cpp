 SIMD_INLINE __m128i FeatureDifference(__m128i value, __m128i lo, __m128i hi)
 {
     return _mm_max_epu8(_mm_subs_epu8(value, hi), _mm_subs_epu8(lo, value));
 }