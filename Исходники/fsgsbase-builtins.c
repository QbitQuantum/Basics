void test_writegsbase_u64(unsigned long long __X)
{
  // CHECK: @llvm.x86.wrgsbase.64
  _writegsbase_u64(__X);
}