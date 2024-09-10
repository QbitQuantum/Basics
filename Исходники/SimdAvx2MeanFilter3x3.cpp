 template<bool align> SIMD_INLINE __m256i AverageRow(const Buffer & buffer, size_t offset)
 {
     return _mm256_packus_epi16(AverageRow16<align>(buffer, offset), AverageRow16<align>(buffer, offset + HA));
 }