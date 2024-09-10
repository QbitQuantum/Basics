static void ConvertBGRAToBGR_SSE2(const uint32_t* src,
                                  int num_pixels, uint8_t* dst) {
  const __m128i mask_l = _mm_set_epi32(0, 0x00ffffff, 0, 0x00ffffff);
  const __m128i mask_h = _mm_set_epi32(0x00ffffff, 0, 0x00ffffff, 0);
  const __m128i* in = (const __m128i*)src;
  const uint8_t* const end = dst + num_pixels * 3;
  // the last storel_epi64 below writes 8 bytes starting at offset 18
  while (dst + 26 <= end) {
    const __m128i bgra0 = _mm_loadu_si128(in++);     // bgra0|bgra1|bgra2|bgra3
    const __m128i bgra4 = _mm_loadu_si128(in++);     // bgra4|bgra5|bgra6|bgra7
    const __m128i a0l = _mm_and_si128(bgra0, mask_l);   // bgr0|0|bgr0|0
    const __m128i a4l = _mm_and_si128(bgra4, mask_l);   // bgr0|0|bgr0|0
    const __m128i a0h = _mm_and_si128(bgra0, mask_h);   // 0|bgr0|0|bgr0
    const __m128i a4h = _mm_and_si128(bgra4, mask_h);   // 0|bgr0|0|bgr0
    const __m128i b0h = _mm_srli_epi64(a0h, 8);         // 000b|gr00|000b|gr00
    const __m128i b4h = _mm_srli_epi64(a4h, 8);         // 000b|gr00|000b|gr00
    const __m128i c0 = _mm_or_si128(a0l, b0h);          // rgbrgb00|rgbrgb00
    const __m128i c4 = _mm_or_si128(a4l, b4h);          // rgbrgb00|rgbrgb00
    const __m128i c2 = _mm_srli_si128(c0, 8);
    const __m128i c6 = _mm_srli_si128(c4, 8);
    _mm_storel_epi64((__m128i*)(dst +   0), c0);
    _mm_storel_epi64((__m128i*)(dst +   6), c2);
    _mm_storel_epi64((__m128i*)(dst +  12), c4);
    _mm_storel_epi64((__m128i*)(dst +  18), c6);
    dst += 24;
    num_pixels -= 8;
  }
  // left-overs
  if (num_pixels > 0) {
    VP8LConvertBGRAToBGR_C((const uint32_t*)in, num_pixels, dst);
  }
}