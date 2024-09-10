__m512i test_mm512_maskz_multishift_epi64_epi8(__mmask64 __M, __m512i __X, __m512i __Y) {
  // CHECK-LABEL: @test_mm512_maskz_multishift_epi64_epi8
  // CHECK: @llvm.x86.avx512.mask.pmultishift.qb.512
  return _mm512_maskz_multishift_epi64_epi8(__M, __X, __Y); 
}