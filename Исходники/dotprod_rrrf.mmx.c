// use MMX/SSE extensions
void dotprod_rrrf_execute_mmx(dotprod_rrrf _q,
                              float *      _x,
                              float *      _y)
{
    // first cut: ...
    __m128 v;   // input vector
    __m128 h;   // coefficients vector
    __m128 s;   // dot product
    __m128 sum = _mm_setzero_ps(); // load zeros into sum register

    // t = 4*(floor(_n/4))
    unsigned int t = (_q->n >> 2) << 2;

    //
    unsigned int i;
    for (i=0; i<t; i+=4) {
        // load inputs into register (unaligned)
        v = _mm_loadu_ps(&_x[i]);

        // load coefficients into register (aligned)
        h = _mm_load_ps(&_q->h[i]);

        // compute multiplication
        s = _mm_mul_ps(v, h);
       
        // parallel addition
        sum = _mm_add_ps( sum, s );
    }

    // aligned output array
    float w[4] __attribute__((aligned(16)));

#if HAVE_PMMINTRIN_H
    // fold down into single value
    __m128 z = _mm_setzero_ps();
    sum = _mm_hadd_ps(sum, z);
    sum = _mm_hadd_ps(sum, z);
   
    // unload single (lower value)
    _mm_store_ss(w, sum);
    float total = w[0];
#else
    // unload packed array
    _mm_store_ps(w, sum);
    float total = w[0] + w[1] + w[2] + w[3];
#endif

    // cleanup
    for (; i<_q->n; i++)
        total += _x[i] * _q->h[i];

    // set return value
    *_y = total;
}