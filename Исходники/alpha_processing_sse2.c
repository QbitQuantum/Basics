static void MultARGBRow(uint32_t* const ptr, int width, int inverse) {
  int x = 0;
  if (!inverse) {
    const int kSpan = 2;
    const __m128i zero = _mm_setzero_si128();
    const __m128i kRound =
        _mm_set_epi16(0, 1 << 7, 1 << 7, 1 << 7, 0, 1 << 7, 1 << 7, 1 << 7);
    const __m128i kMult =
        _mm_set_epi16(0, 0x0101, 0x0101, 0x0101, 0, 0x0101, 0x0101, 0x0101);
    const __m128i kOne64 = _mm_set_epi16(1u << 8, 0, 0, 0, 1u << 8, 0, 0, 0);
    const int w2 = width & ~(kSpan - 1);
    for (x = 0; x < w2; x += kSpan) {
      const __m128i argb0 = _mm_loadl_epi64((__m128i*)&ptr[x]);
      const __m128i argb1 = _mm_unpacklo_epi8(argb0, zero);
      const __m128i tmp0 = _mm_shufflelo_epi16(argb1, _MM_SHUFFLE(3, 3, 3, 3));
      const __m128i tmp1 = _mm_shufflehi_epi16(tmp0, _MM_SHUFFLE(3, 3, 3, 3));
      const __m128i tmp2 = _mm_srli_epi64(tmp1, 16);
      const __m128i scale0 = _mm_mullo_epi16(tmp1, kMult);
      const __m128i scale1 = _mm_or_si128(tmp2, kOne64);
      const __m128i argb2 = _mm_mulhi_epu16(argb1, scale0);
      const __m128i argb3 = _mm_mullo_epi16(argb1, scale1);
      const __m128i argb4 = _mm_adds_epu16(argb2, argb3);
      const __m128i argb5 = _mm_adds_epu16(argb4, kRound);
      const __m128i argb6 = _mm_srli_epi16(argb5, 8);
      const __m128i argb7 = _mm_packus_epi16(argb6, zero);
      _mm_storel_epi64((__m128i*)&ptr[x], argb7);
    }
  }
  width -= x;
  if (width > 0) WebPMultARGBRowC(ptr + x, width, inverse);
}