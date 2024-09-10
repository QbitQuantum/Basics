__m128i test_mm_clmulepi64_si128(__m128i a, __m128i b) {
  // CHECK: @llvm.x86.pclmulqdq
  return _mm_clmulepi64_si128(a, b, 0);
}