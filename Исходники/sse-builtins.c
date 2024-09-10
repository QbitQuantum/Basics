__m128i test_mm_mpsadbw_epu8(__m128i x, __m128i y) {
  // CHECK: define {{.*}} @test_mm_mpsadbw_epu8
  // CHECK: @llvm.x86.sse41.mpsadbw
  return _mm_mpsadbw_epu8(x, y, 1);
}