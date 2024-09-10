 SIMD_INLINE void PackResult32i(const uint32_t * src, uint8_t * dst)
 {
     __m128i lo = _mm_packus_epi32(_mm_loadu_si128((__m128i*)src + 0), _mm_loadu_si128((__m128i*)src + 1));
     __m128i hi = _mm_packus_epi32(_mm_loadu_si128((__m128i*)src + 2), _mm_loadu_si128((__m128i*)src + 3));
     _mm_storeu_si128((__m128i*)dst, _mm_packus_epi16(lo, hi));
 }