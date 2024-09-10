static WEBP_INLINE void YuvToBgrSSE2(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const bgr) {
  const __m128i tmp0 = GetRGBA32b(y, u, v);
  const __m128i tmp1 = _mm_shuffle_epi32(tmp0, _MM_SHUFFLE(3, 0, 1, 2));
  const __m128i tmp2 = _mm_packs_epi32(tmp1, tmp1);
  const __m128i tmp3 = _mm_packus_epi16(tmp2, tmp2);
  // Note: we store 8 bytes at a time, not 3 bytes! -> memory stomp
  _mm_storel_epi64((__m128i*)bgr, tmp3);
}