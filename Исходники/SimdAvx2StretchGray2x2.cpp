 template<bool align> SIMD_INLINE void StoreUnpacked(__m256i value, uint8_t * dst)
 {
     Store<align>((__m256i*)(dst + 0), _mm256_unpacklo_epi8(value, value));
     Store<align>((__m256i*)(dst + A), _mm256_unpackhi_epi8(value, value));
 }