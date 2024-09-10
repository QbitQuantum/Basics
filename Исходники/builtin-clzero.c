void test_mm_clzero(void * __m) {
  //CHECK-LABEL: @test_mm_clzero
  //CHECK: @llvm.x86.clzero
  _mm_clzero(__m);
}