__m128i test_mm_abs_epi32(__m128i a) {
  // CHECK-LABEL: test_mm_abs_epi32
  // CHECK: call <4 x i32> @llvm.x86.ssse3.pabs.d.128
  return _mm_abs_epi32(a);
}