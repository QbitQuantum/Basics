    float DotProductSIMD(const float* a, const float* b, std::size_t n) {
        std::size_t i = 0;

        __m128 sum =  _mm_setzero_ps();
        for(; i < ROUND_DOWN(n, 4); i += 4) {
            __m128 x = _mm_loadu_ps(a + i);
            __m128 y = _mm_loadu_ps(a + i);
            x = _mm_mul_ps(x, y);
            sum = _mm_add_ps(x, sum);
        }

        sum = _mm_hadd_ps(sum, sum);
        sum = _mm_hadd_ps(sum, sum);
        float product = _mm_cvtss_f32(sum);

        for(; i < n; i++) {
            product += a[i] * b[i];
        }
        return product;
    }