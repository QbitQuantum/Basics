__m128i __attribute__((__target__("sse4a"))) mm_extract_si64_wrap(__m128i x, __m128i y) {
  return _mm_extract_si64(x, y);
}