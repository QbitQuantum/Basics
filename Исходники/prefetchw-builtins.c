void test_m_prefetch(void *p) {
  return _m_prefetch(p);
// CHECK-LABEL: define void @test_m_prefetch
// CHECK: call void @llvm.prefetch({{.*}}, i32 0, i32 3, i32 1)
}