static void SubtractGreenFromBlueAndRed(uint32_t* argb_data, int num_pixels) {
  const __m128i mask = _mm_set1_epi32(0x0000ff00);
  int i;
  for (i = 0; i + 4 <= num_pixels; i += 4) {
    const __m128i in = _mm_loadu_si128((__m128i*)&argb_data[i]);
    const __m128i in_00g0 = _mm_and_si128(in, mask);     // 00g0|00g0|...
    const __m128i in_0g00 = _mm_slli_epi32(in_00g0, 8);  // 0g00|0g00|...
    const __m128i in_000g = _mm_srli_epi32(in_00g0, 8);  // 000g|000g|...
    const __m128i in_0g0g = _mm_or_si128(in_0g00, in_000g);
    const __m128i out = _mm_sub_epi8(in, in_0g0g);
    _mm_storeu_si128((__m128i*)&argb_data[i], out);
  }
  // fallthrough and finish off with plain-C
  VP8LSubtractGreenFromBlueAndRed_C(argb_data + i, num_pixels - i);
}