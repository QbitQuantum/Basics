__m128d test_cmp_ss(__m128 a, __m128 b) {
  // Expects that the third argument in LLVM IR is immediate expression
  // CHECK: @llvm.x86.sse.cmp.ss({{.*}}, i8 13)
  return _mm_cmp_ss(a, b, _CMP_GE_OS);
}