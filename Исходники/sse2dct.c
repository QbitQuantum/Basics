OD_SIMD_INLINE __m128i od_dct_mul_epi32(__m128i val, int32_t scale,
 int32_t offset, int32_t shift) {
  return _mm_srai_epi32(_mm_add_epi32(OD_MULLO_EPI32(val, scale),
   _mm_set1_epi32(offset)), shift);
}