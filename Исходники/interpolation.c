static inline __m128
lanczos_sse(__m128 width, __m128 t)
{
    /* Compute a value for sinf(pi.t) in [-pi pi] for which the value will be
     * correct */
    __m128i a = _mm_cvtps_epi32(t);
    __m128 r = _mm_sub_ps(t, _mm_cvtepi32_ps(a));

    // Compute the correct sign for sinf(pi.r)
    static const uint32_t fone[] __attribute__((aligned(SSE_ALIGNMENT))) = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000};
    static const uint32_t ione[] __attribute__((aligned(SSE_ALIGNMENT))) = { 1, 1, 1, 1};
    static const __m128 eps = {DT_LANCZOS_EPSILON, DT_LANCZOS_EPSILON, DT_LANCZOS_EPSILON, DT_LANCZOS_EPSILON};
    static const __m128 pi = {M_PI, M_PI, M_PI, M_PI};
    static const __m128 pi2 = {M_PI*M_PI, M_PI*M_PI, M_PI*M_PI, M_PI*M_PI};

    __m128i isign = _mm_and_si128(*(__m128i*)ione, a);
    isign = _mm_slli_epi64(isign, 31);
    isign = _mm_or_si128(*(__m128i*)fone, isign);
    __m128 fsign = _mm_castsi128_ps(isign);

    __m128 num = _mm_mul_ps(width, fsign);
    num = _mm_mul_ps(num, sinf_fast_sse(_mm_mul_ps(pi, r)));
    num = _mm_mul_ps(num, sinf_fast_sse(_mm_div_ps(_mm_mul_ps(pi, t), width)));
    num = _mm_add_ps(eps, num);

    __m128 den = _mm_mul_ps(pi2, _mm_mul_ps(t, t));
    den = _mm_add_ps(eps, den);

    return _mm_div_ps(num, den);
}