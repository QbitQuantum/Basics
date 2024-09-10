void test_wrpkru(unsigned int __A) {
  // CHECK-LABEL: @test_wrpkru
  // CHECK: @llvm.x86.wrpkru
  _wrpkru(__A);
  return ;
}