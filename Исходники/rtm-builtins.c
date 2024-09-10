unsigned int test_xtest(void) {
  // CHECK: i32 @llvm.x86.xtest()
  return _xtest();
}