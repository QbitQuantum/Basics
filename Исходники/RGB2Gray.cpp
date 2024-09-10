void sse_rgb2gray(float* ra, float* ga, float* ba, float* gray) {
    __m128 c1 =  _mm_set1_ps(0.3f);
    __m128 c2 =  _mm_set1_ps(0.59f);
    __m128 c3 =  _mm_set1_ps(0.11f);

    for(int i = 0; i < N; i+=4) {
        __m128 a = _mm_loadu_ps(ra+i);
        __m128 b = _mm_loadu_ps(ga+i);
        __m128 c = _mm_loadu_ps(ba+i);
        __m128 ab = _mm_add_ps(_mm_mul_ps(c1, a), _mm_mul_ps(c2, b));
        __m128 out = _mm_add_ps(ab, _mm_mul_ps(c3, c));
        _mm_storeu_ps(gray+i, out);
    }
}