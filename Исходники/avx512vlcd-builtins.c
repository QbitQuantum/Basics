__m256i test_mm256_maskz_lzcnt_epi64(__mmask8 __U, __m256i __A) {
  // CHECK-LABEL: @test_mm256_maskz_lzcnt_epi64
  // CHECK: @llvm.x86.avx512.mask.lzcnt.q
  return _mm256_maskz_lzcnt_epi64(__U, __A); 
}