void test_alloca(int n) {
  capture(_alloca(n));
  // CHECK: %[[arg:.*]] = alloca i8, i32 %{{.*}}, align 16
  // CHECK: call void @capture(i8* %[[arg]])
}