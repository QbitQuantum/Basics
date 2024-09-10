__m256i test_mm256_insertf128_si256_0(__m256i a, __m128i b) {
  // CHECK-LABEL: @test_mm256_insertf128_si256_0
  // CHECK: shufflevector{{.*}}<i32 4, i32 5, i32 2, i32 3>
  return _mm256_insertf128_si256(a, b, 0);
}