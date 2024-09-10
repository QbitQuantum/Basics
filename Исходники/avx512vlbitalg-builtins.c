__mmask32 test_mm256_mask_bitshuffle_epi64_mask(__mmask32 __U, __m256i __A, __m256i __B) {
  // CHECK-LABEL: @test_mm256_mask_bitshuffle_epi64_mask
  // CHECK: @llvm.x86.avx512.mask.vpshufbitqmb.256
  return _mm256_mask_bitshuffle_epi64_mask(__U, __A, __B);
}