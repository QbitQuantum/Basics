static double vecsum(const double *buf, int num_doubles)
{
    int i;
    double hi, lo;
    __m128d x0, x1, x2, x3, x4, x5, x6, x7;
    __m128d sum0 = _mm_set_pd(0.0,0.0);
    __m128d sum1 = _mm_set_pd(0.0,0.0);
    __m128d sum2 = _mm_set_pd(0.0,0.0);
    __m128d sum3 = _mm_set_pd(0.0,0.0);
    __m128d sum4 = _mm_set_pd(0.0,0.0);
    __m128d sum5 = _mm_set_pd(0.0,0.0);
    __m128d sum6 = _mm_set_pd(0.0,0.0);
    __m128d sum7 = _mm_set_pd(0.0,0.0);
    for (i = 0; i < num_doubles; i+=DOUBLES_PER_LOOP_ITER) {
        x0 = _mm_load_pd(buf + i + 0);
        x1 = _mm_load_pd(buf + i + 2);
        x2 = _mm_load_pd(buf + i + 4);
        x3 = _mm_load_pd(buf + i + 6);
        x4 = _mm_load_pd(buf + i + 8);
        x5 = _mm_load_pd(buf + i + 10);
        x6 = _mm_load_pd(buf + i + 12);
        x7 = _mm_load_pd(buf + i + 14);
        sum0 = _mm_add_pd(sum0, x0);
        sum1 = _mm_add_pd(sum1, x1);
        sum2 = _mm_add_pd(sum2, x2);
        sum3 = _mm_add_pd(sum3, x3);
        sum4 = _mm_add_pd(sum4, x4);
        sum5 = _mm_add_pd(sum5, x5);
        sum6 = _mm_add_pd(sum6, x6);
        sum7 = _mm_add_pd(sum7, x7);
    }
    x0 = _mm_add_pd(sum0, sum1);
    x1 = _mm_add_pd(sum2, sum3);
    x2 = _mm_add_pd(sum4, sum5);
    x3 = _mm_add_pd(sum6, sum7);
    x4 = _mm_add_pd(x0, x1);
    x5 = _mm_add_pd(x2, x3);
    x6 = _mm_add_pd(x4, x5);
    _mm_storeh_pd(&hi, x6);
    _mm_storel_pd(&lo, x6);
    return hi + lo;
}