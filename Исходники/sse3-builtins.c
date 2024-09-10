__m128i test_mm_lddqu_si128(__m128i const* P) {
  // CHECK-LABEL: test_mm_lddqu_si128
  // CHECK: call <16 x i8> @llvm.x86.sse3.ldu.dq(i8* %{{.*}})
  return _mm_lddqu_si128(P);
}