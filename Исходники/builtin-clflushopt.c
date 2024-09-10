void test_mm_clflushopt(char * __m) {
  //CHECK-LABLE: @test_mm_clflushopt
  //CHECK: @llvm.x86.clflushopt
  _mm_clflushopt(__m);
}