double CMercerKernel<float>::Evaluate(float* x, float* y) {

#ifndef __SSE4_1__

    float result = 0;

    for(size_t i=0; i<m_n; i++)
        result += x[i]*y[i];

    return static_cast<double>(result);

#else
    __m128* px = reinterpret_cast<__m128*>(x);
    __m128* py = reinterpret_cast<__m128*>(y);

    float zero = 0.0;
    __m128 sum = _mm_load1_ps(&zero);

    const int mask = 241;       // 4 MSB mask input, 4 LSB mask output

    for(size_t i=0; i<m_offset/4; i++) {

        __m128 temp = _mm_dp_ps(px[i],py[i],mask);
        sum = _mm_add_ss(sum,temp);                         // accumulate result in first register

    }

    float result[4] = {0.0,0.0,0.0,0.0};
    _mm_storeu_ps(result,sum);

    // add offset
    for(size_t i=m_offset; i<m_n; i++)
        result[0] += x[i]*y[i];

    return static_cast<double>(result[0]);
#endif

}