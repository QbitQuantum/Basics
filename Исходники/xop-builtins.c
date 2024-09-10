__m256d test_mm256_permute2_pd(__m256d a, __m256d b, __m256i c) {
  // CHECK-LABEL: test_mm256_permute2_pd
  // CHECK: @llvm.x86.xop.vpermil2pd.256
  return _mm256_permute2_pd(a, b, c, 0);
}