/* use compiler intrinsics for 4x parallel processing */
static inline float chi2_intrinsic_aligned_float(int n, const float* x, const float* y) {
    float result=0;
    const __m128 eps = _mm_set1_ps(FLT_MIN);
    const __m128 zero = _mm_setzero_ps();
    __m128 chi2 = _mm_setzero_ps();
    
    for (; n>3; n-=4) {
        const __m128 a = _mm_loadu_ps(x);
        const __m128 b = _mm_loadu_ps(y);
        const __m128 a_plus_eps = _mm_add_ps(a,eps);
        const __m128 a_plus_b_plus_eps = _mm_add_ps(a_plus_eps,b);
        const __m128 a_minus_b = _mm_sub_ps(a,b);
        const __m128 a_minus_b_sq = _mm_mul_ps(a_minus_b, a_minus_b);
        const __m128 prod = _mm_div_ps(a_minus_b_sq, a_plus_b_plus_eps);
        chi2 = _mm_add_ps(chi2, prod);
	x+=4;
	y+=4;
    }
    const __m128 shuffle1 = _mm_shuffle_ps(chi2, chi2, _MM_SHUFFLE(1,0,3,2));
    const __m128 sum1 = _mm_add_ps(chi2, shuffle1);
    const __m128 shuffle2 = _mm_shuffle_ps(sum1, sum1, _MM_SHUFFLE(2,3,0,1));
    const __m128 sum2 = _mm_add_ps(sum1, shuffle2);
// with SSE3, we could use hadd_ps, but the difference is negligible 

    _mm_store_ss(&result,sum2);
    _mm_empty();
    
    if (n)
        result += chi2_baseline_float(n, x, y);	// remaining 1-3 entries
    return result;
}