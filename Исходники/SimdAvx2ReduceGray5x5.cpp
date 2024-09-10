 template <bool align> SIMD_INLINE __m256i LoadUnpacked(const void * src)
 {
     return _mm256_cvtepu8_epi16(LoadHalf<align>((const __m128i*)src));
 }