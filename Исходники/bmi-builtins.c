unsigned long long test_andn_u64(unsigned long __X, unsigned long __Y) {
  // CHECK: [[DEST:%.*]] = xor i64 %{{.*}}, -1
  // CHECK-NEXT: %{{.*}} = and i64 [[DEST]], %{{.*}}
  return _andn_u64(__X, __Y);
}