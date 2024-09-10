/* Routine optimized for shuffling a buffer for a type size of 4 bytes. */
static void
shuffle4_sse2(uint8_t* const dest, const uint8_t* const src,
              const size_t vectorizable_elements, const size_t total_elements) {
  static const size_t bytesoftype = 4;
  size_t i;
  int j;
  uint8_t* dest_for_ith_element;
  __m128i xmm0[4], xmm1[4];

  for (i = 0; i < vectorizable_elements; i += sizeof(__m128i)) {
    /* Fetch 16 elements (64 bytes) then transpose bytes and words. */
    for (j = 0; j < 4; j++) {
      xmm0[j] = _mm_loadu_si128((__m128i*)(src + (i * bytesoftype) + (j * sizeof(__m128i))));
      xmm1[j] = _mm_shuffle_epi32(xmm0[j], 0xd8);
      xmm0[j] = _mm_shuffle_epi32(xmm0[j], 0x8d);
      xmm0[j] = _mm_unpacklo_epi8(xmm1[j], xmm0[j]);
      xmm1[j] = _mm_shuffle_epi32(xmm0[j], 0x04e);
      xmm0[j] = _mm_unpacklo_epi16(xmm0[j], xmm1[j]);
    }
    /* Transpose double words */
    for (j = 0; j < 2; j++) {
      xmm1[j * 2] = _mm_unpacklo_epi32(xmm0[j * 2], xmm0[j * 2 + 1]);
      xmm1[j * 2 + 1] = _mm_unpackhi_epi32(xmm0[j * 2], xmm0[j * 2 + 1]);
    }
    /* Transpose quad words */
    for (j = 0; j < 2; j++) {
      xmm0[j * 2] = _mm_unpacklo_epi64(xmm1[j], xmm1[j + 2]);
      xmm0[j * 2 + 1] = _mm_unpackhi_epi64(xmm1[j], xmm1[j + 2]);
    }
    /* Store the result vectors */
    dest_for_ith_element = dest + i;
    for (j = 0; j < 4; j++) {
      _mm_storeu_si128((__m128i*)(dest_for_ith_element + (j * total_elements)), xmm0[j]);
    }
  }
}