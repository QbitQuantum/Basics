void test_mm_stream_ss(float *p, __m128 a) {
  // CHECK-LABEL: test_mm_stream_ss
  // CHECK: call void @llvm.x86.sse4a.movnt.ss(i8* %{{[^,]+}}, <4 x float> %{{[^,]+}})
  _mm_stream_ss(p, a);
}