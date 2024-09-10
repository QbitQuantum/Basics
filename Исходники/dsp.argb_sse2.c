static void PackARGB(const uint8_t* a, const uint8_t* r, const uint8_t* g,
                     const uint8_t* b, int len, uint32_t* out) {
  if (g == r + 1) {  // RGBA input order. Need to swap R and B.
    int i = 0;
    const int len_max = len & ~3;  // max length processed in main loop
    const __m128i red_blue_mask = _mm_set1_epi32(0x00ff00ffu);
    assert(b == r + 2);
    assert(a == r + 3);
    for (; i < len_max; i += 4) {
      const __m128i A = _mm_loadu_si128((const __m128i*)(r + 4 * i));
      const __m128i B = _mm_and_si128(A, red_blue_mask);     // R 0 B 0
      const __m128i C = _mm_andnot_si128(red_blue_mask, A);  // 0 G 0 A
      const __m128i D = _mm_shufflelo_epi16(B, _MM_SHUFFLE(2, 3, 0, 1));
      const __m128i E = _mm_shufflehi_epi16(D, _MM_SHUFFLE(2, 3, 0, 1));
      const __m128i F = _mm_or_si128(E, C);
      _mm_storeu_si128((__m128i*)(out + i), F);
    }
    for (; i < len; ++i) {
      out[i] = MakeARGB32(a[4 * i], r[4 * i], g[4 * i], b[4 * i]);
    }
  } else {
    assert(g == b + 1);
    assert(r == b + 2);
    assert(a == b + 3);
    memcpy(out, b, len * 4);
  }
}