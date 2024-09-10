__m128 test_mm_reduce_ss(__m128 __A, __m128 __B) {
  // CHECK-LABEL: @test_mm_reduce_ss
  // CHECK: @llvm.x86.avx512.mask.reduce.ss
  return _mm_reduce_ss(__A, __B, 4);
}