unsigned long long test_pext_u64(unsigned long long __X, unsigned long long __Y) {
  // CHECK: @llvm.x86.bmi.pext.64
  return _pext_u64(__X, __Y);
}