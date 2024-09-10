__m512i test_mm512_maskz_lzcnt_epi64(__mmask8 __U, __m512i __A) {
  // CHECK-LABEL: @test_mm512_maskz_lzcnt_epi64
  // CHECK: @llvm.x86.avx512.mask.lzcnt.q.512
  return _mm512_maskz_lzcnt_epi64(__U,__A); 
}