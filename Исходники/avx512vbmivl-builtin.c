__m256i test_mm256_maskz_multishift_epi64_epi8(__mmask32 __M, __m256i __X, __m256i __Y) {
  // CHECK-LABEL: @test_mm256_maskz_multishift_epi64_epi8
  // CHECK: @llvm.x86.avx512.mask.pmultishift.qb.256
  return _mm256_maskz_multishift_epi64_epi8(__M, __X, __Y); 
}