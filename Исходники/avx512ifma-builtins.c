__m512i test_mm512_maskz_madd52lo_epu64(__mmask8 __M, __m512i __X, __m512i __Y, __m512i __Z) {
  // CHECK-LABEL: @test_mm512_maskz_madd52lo_epu64
  // CHECK: @llvm.x86.avx512.mask.vpmadd52l.uq.512
  return _mm512_maskz_madd52lo_epu64(__M, __X, __Y, __Z); 
}