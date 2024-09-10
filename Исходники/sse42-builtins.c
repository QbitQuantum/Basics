unsigned long long test_mm_crc32_u64(unsigned long long CRC, unsigned long long V) {
  // CHECK-LABEL: test_mm_crc32_u64
  // CHECK: call i64 @llvm.x86.sse42.crc32.64.64(i64 %{{.*}}, i64 %{{.*}})
  return _mm_crc32_u64(CRC, V);
}