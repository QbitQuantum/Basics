__mmask16 test_mm256_mask_cmpneq_epu16_mask(__mmask32 __u, __m256i __a, __m256i __b) {
    // CHECK-LABEL: @test_mm256_mask_cmpneq_epu16_mask
    // CHECK: @llvm.x86.avx512.mask.ucmp.w.256(<16 x i16> {{.*}}, <16 x i16> {{.*}}, i8 4, i16 {{.*}})
    return (__mmask32)_mm256_mask_cmpneq_epu16_mask(__u, __a, __b);
}