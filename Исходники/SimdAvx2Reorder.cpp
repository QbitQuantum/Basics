 template <bool align> SIMD_INLINE void Reorder64bit(const uint8_t * src, uint8_t * dst)
 {
     __m256i _src = Load<align>((__m256i*)src);
     Store<align>((__m256i*)dst, _mm256_shuffle_epi8(_src, K8_SHUFFLE_REORDER_64));
 }