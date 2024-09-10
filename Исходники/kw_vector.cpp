kw_mat4 kw_mul(kw_mat4 m1, kw_mat4 m2){
    __m128 c0 = _mm_set_ps(m2.rc[3][0], m2.rc[2][0], m2.rc[1][0], m2.rc[0][0]);
    __m128 c1 = _mm_set_ps(m2.rc[3][1], m2.rc[2][1], m2.rc[1][1], m2.rc[0][1]);
    __m128 c2 = _mm_set_ps(m2.rc[3][2], m2.rc[2][2], m2.rc[1][2], m2.rc[0][2]);
    __m128 c3 = _mm_set_ps(m2.rc[3][3], m2.rc[2][3], m2.rc[1][3], m2.rc[0][3]);
    
    kw_mat4 result;
    result.rc[0][0] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[0], c0, 0xf1));
    result.rc[0][1] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[0], c1, 0xf1));
    result.rc[0][2] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[0], c2, 0xf1));
    result.rc[0][3] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[0], c3, 0xf1));
    
    result.rc[1][0] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[1], c0, 0xf1));
    result.rc[1][1] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[1], c1, 0xf1));
    result.rc[1][2] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[1], c2, 0xf1));
    result.rc[1][3] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[1], c3, 0xf1));
    
    result.rc[2][0] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[2], c0, 0xf1));
    result.rc[2][1] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[2], c1, 0xf1));
    result.rc[2][2] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[2], c2, 0xf1));
    result.rc[2][3] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[2], c3, 0xf1));
    
    result.rc[3][0] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[3], c0, 0xf1));
    result.rc[3][1] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[3], c1, 0xf1));
    result.rc[3][2] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[3], c2, 0xf1));
    result.rc[3][3] = _mm_cvtss_f32(_mm_dp_ps(m1.simd[3], c3, 0xf1));
    return result;
}