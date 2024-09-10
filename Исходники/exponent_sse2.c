int
exponent_sum_square_error_sse2(uint8_t *exp0, uint8_t *exp1, int ncoefs)
{
    int i, err;
    int exp_error = 0;
    union {
        __m128i v;
        int32_t res[4];
    } ures;
    __m128i vzero = _mm_setzero_si128();
    __m128i vres = vzero;

    for (i = 0; i < (ncoefs & ~15); i+=16) {
        __m128i vexp = _mm_loadu_si128((__m128i*)&exp0[i]);
        __m128i vexp2 = _mm_loadu_si128((__m128i*)&exp1[i]);
#if 0
        //safer but needed?
        __m128i vexphi = _mm_unpackhi_epi8(vexp, vzero);
        __m128i vexp2hi = _mm_unpackhi_epi8(vexp2, vzero);
        __m128i vexplo = _mm_unpacklo_epi8(vexp, vzero);
        __m128i vexp2lo = _mm_unpacklo_epi8(vexp2, vzero);
        __m128i verrhi = _mm_sub_epi16(vexphi, vexp2hi);
        __m128i verrlo = _mm_sub_epi16(vexplo, vexp2lo);
#else
        __m128i verr = _mm_sub_epi8(vexp, vexp2);
        __m128i vsign = _mm_cmplt_epi8(verr, vzero);
        __m128i verrhi = _mm_unpackhi_epi8(verr, vsign);
        __m128i verrlo = _mm_unpacklo_epi8(verr, vsign);
#endif
        verrhi = _mm_madd_epi16(verrhi, verrhi);
        verrlo = _mm_madd_epi16(verrlo, verrlo);
        verrhi = _mm_add_epi32(verrhi, verrlo);
        vres = _mm_add_epi32(vres, verrhi);
    }
    _mm_store_si128(&ures.v, vres);
    ures.res[0]+=ures.res[1];
    ures.res[2]+=ures.res[3];
    exp_error += ures.res[0]+ures.res[2];
    for (; i < ncoefs; ++i) {
        err = exp0[i] - exp1[i];
        exp_error += (err * err);
    }
    return exp_error;
}