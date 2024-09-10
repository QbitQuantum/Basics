 inline
 void scatter(float *ptr, const int *offsets) const
 {
     __m512i indices;
     SHORTVEC_ASSERT_ALIGNED(offsets, 64);
     indices = _mm512_load_epi32(offsets);
     _mm512_i32scatter_ps(ptr, indices, val1, 4);
     indices = _mm512_load_epi32(offsets + 16);
     _mm512_i32scatter_ps(ptr, indices, val2, 4);
 }