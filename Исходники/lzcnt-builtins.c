unsigned long long test__lzcnt_u64(unsigned long long __X)
{
  // CHECK: @llvm.ctlz.i64
  return _lzcnt_u64(__X);
}