__mmask32 test_mm512_mask_cmpneq_epu16_mask(__mmask32 __u, __m512i __a, __m512i __b) {
  // CHECK-LABEL: @test_mm512_mask_cmpneq_epu16_mask
  // CHECK: @llvm.x86.avx512.mask.ucmp.w.512(<32 x i16> {{.*}}, <32 x i16> {{.*}}, i8 4, i32 {{.*}})
  return (__mmask32)_mm512_mask_cmpneq_epu16_mask(__u, __a, __b);
}