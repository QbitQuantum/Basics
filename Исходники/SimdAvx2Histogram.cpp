 SIMD_INLINE void MaskSrc(const uint8_t * src, const uint8_t * mask, const __m256i & index, ptrdiff_t offset, uint16_t * dst)
 {
     const __m256i _src = Load<srcAlign>((__m256i*)(src + offset));
     const __m256i _mask = _mm256_and_si256(_mm256_cmpeq_epi8(Load<srcAlign>((__m256i*)(mask + offset)), index), K8_01);
     __m256i lo = _mm256_mullo_epi16(_mm256_add_epi16(K16_0008, UnpackU8<0>(_src)), UnpackU8<0>(_mask));
     __m256i hi = _mm256_mullo_epi16(_mm256_add_epi16(K16_0008, UnpackU8<1>(_src)), UnpackU8<1>(_mask));
     Store<dstAlign>((__m256i*)(dst + offset) + 0, _mm256_permute2x128_si256(lo, hi, 0x20)); 
     Store<dstAlign>((__m256i*)(dst + offset) + 1, _mm256_permute2x128_si256(lo, hi, 0x31));
 }