static void HE16(uint8_t* dst) {     // horizontal
  int j;
  const __m128i kShuffle3 = _mm_set1_epi8(3);
  for (j = 16; j > 0; --j) {
    const __m128i in = _mm_cvtsi32_si128(*(int*)(dst - 4));
    const __m128i values = _mm_shuffle_epi8(in, kShuffle3);
    _mm_storeu_si128((__m128i*)dst, values);
    dst += BPS;
  }
}