__m128 test_rsqrt_ss(__m128 x) {
  // CHECK: define {{.*}} @test_rsqrt_ss
  // CHECK: call <4 x float> @llvm.x86.sse.rsqrt.ss({{.*}}, !dbg !{{.*}}
  // CHECK: ret <4 x float>
  return _mm_rsqrt_ss(x);
}