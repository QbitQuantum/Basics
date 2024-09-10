void lx_matmul_sse3_aligned(const float *in_A,
                            const float *in_x,
                            const float *out_y,
                            LXInteger n)
{
    __m128 A0 = _mm_load_ps((const float *)(in_A + 0));
    __m128 A1 = _mm_load_ps((const float *)(in_A + 4));
    __m128 A2 = _mm_load_ps((const float *)(in_A + 8));
    __m128 A3 = _mm_load_ps((const float *)(in_A + 12));
    
    for (LXInteger i = 0; i < n; i++) {
        __m128 x =  _mm_load_ps((const float*)(in_x + i*4));
        __m128 m0 = _mm_mul_ps(A0, x);
        __m128 m1 = _mm_mul_ps(A1, x);
        __m128 m2 = _mm_mul_ps(A2, x);
        __m128 m3 = _mm_mul_ps(A3, x);
        __m128 sum_01 = _mm_hadd_ps(m0, m1); 
        __m128 sum_23 = _mm_hadd_ps(m2, m3);
        __m128 result = _mm_hadd_ps(sum_01, sum_23);
        _mm_store_ps((float*)(out_y + i*4), result);
    }
}