/* use compiler intrinsics for 2x parallel processing */
static inline double chi2_intrinsic_double(int n, const double* x, const double* y) {
    double result=0;
    const __m128d eps = _mm_set1_pd(DBL_MIN);
    const __m128d zero = _mm_setzero_pd();
    __m128d chi2 = _mm_setzero_pd();    

    for ( ; n>1; n-=2) {
        const __m128d a = _mm_loadu_pd(x);
        const __m128d b = _mm_loadu_pd(y);
	x+=2;
	y+=2;
        const __m128d a_plus_b = _mm_add_pd(a,b);
        const __m128d a_plus_b_plus_eps = _mm_add_pd(a_plus_b,eps);
        const __m128d a_minus_b = _mm_sub_pd(a,b);
        const __m128d a_minus_b_sq = _mm_mul_pd(a_minus_b, a_minus_b);
        const __m128d quotient = _mm_div_pd(a_minus_b_sq, a_plus_b_plus_eps);
        chi2 = _mm_add_pd(chi2, quotient);
    }
    const __m128d shuffle = _mm_shuffle_pd(chi2, chi2, _MM_SHUFFLE2(0,1));
    const __m128d sum = _mm_add_pd(chi2, shuffle);
// with SSE3, we could use hadd_pd, but the difference is negligible 

    _mm_store_sd(&result,sum);
    _mm_empty();
    if (n)
        result += chi2_baseline_double(n, x, y); // remaining entries
    return result;
}