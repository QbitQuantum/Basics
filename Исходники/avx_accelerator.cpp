    __m256 distance(const __m256& x1, const __m256& y1, const __m256& x2, const __m256& y2)
    {
        const __m256 x_diff = _mm256_sub_ps(x1, x2);
        const __m256 y_diff = _mm256_sub_ps(y1, y2);
        const __m256 x_diff2 = _mm256_mul_ps(x_diff, x_diff);
        const __m256 y_diff2 = _mm256_mul_ps(y_diff, y_diff);
        const __m256 sum = _mm256_add_ps(x_diff2, y_diff2);
        const __m256 dist = _mm256_sqrt_ps(sum);

        return dist;
    }