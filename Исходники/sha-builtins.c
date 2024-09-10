__m128i test_sha256rnds2(__m128i a, __m128i b, __m128i c) {
  // CHECK: call <4 x i32> @llvm.x86.sha256rnds2
  return _mm_sha256rnds2_epu32(a, b, c);
}