long long test_mm512_mask_reduce_or_epi64(__mmask8 __M, __m512i __W){
  // CHECK: {{.*}} = bitcast i8 %__M to <8 x i1>
  // CHECK: {{.*}} = select <8 x i1> {{.*}}, <8 x i64> %__W, <8 x i64> zeroinitializer
  // CHECK: %shuffle.i = shufflevector <8 x i64> {{.*}}, <8 x i64> undef, <4 x i32> <i32 0, i32 1, i32 2, i32 3>
  // CHECK: %shuffle1.i = shufflevector <8 x i64> {{.*}}, <8 x i64> undef, <4 x i32> <i32 4, i32 5, i32 6, i32 7>
  // CHECK: %or.i = or <4 x i64> %shuffle.i, %shuffle1.i
  // CHECK: %shuffle2.i = shufflevector <4 x i64> %or.i, <4 x i64> undef, <2 x i32> <i32 0, i32 1>
  // CHECK: %shuffle3.i = shufflevector <4 x i64> %or.i, <4 x i64> undef, <2 x i32> <i32 2, i32 3>
  // CHECK: %or4.i = or <2 x i64> %shuffle2.i, %shuffle3.i
  // CHECK: %shuffle6.i = shufflevector <2 x i64> %or4.i, <2 x i64> undef, <2 x i32> <i32 1, i32 undef>
  // CHECK: %or7.i = or <2 x i64> %shuffle6.i, %or4.i
  // CHECK: %vecext.i = extractelement <2 x i64> %or7.i, i32 0
  // CHECK: ret i64 %vecext.i
  return _mm512_mask_reduce_or_epi64(__M, __W); 
}