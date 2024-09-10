// use MMX/SSE extensions
void dotprod_crcf_execute_mmx(dotprod_crcf _q,
                              float complex * _x,
                              float complex * _y)
{
    // type cast input as floating point array
    float * x = (float*) _x;

    // double effective length
    unsigned int n = 2*_q->n;

    // first cut: ...
    __m128 v;   // input vector
    __m128 h;   // coefficients vector
    __m128 s;   // dot product
    __m128 sum = _mm_setzero_ps();  // load zeros into sum register

    // t = 4*(floor(_n/4))
    unsigned int t = (n >> 2) << 2;

    //
    unsigned int i;
    for (i=0; i<t; i+=4) {
        // load inputs into register (unaligned)
        v = _mm_loadu_ps(&x[i]);

        // load coefficients into register (aligned)
        h = _mm_load_ps(&_q->h[i]);

        // compute multiplication
        s = _mm_mul_ps(v, h);

        // accumulate
        sum = _mm_add_ps(sum, s);
    }

    // aligned output array
    float w[4] __attribute__((aligned(16)));

    // unload packed array
    _mm_store_ps(w, sum);

    // add in-phase and quadrature components
    w[0] += w[2];
    w[1] += w[3];

    // cleanup (note: n _must_ be even)
    for (; i<n; i+=2) {
        w[0] += x[i  ] * _q->h[i  ];
        w[1] += x[i+1] * _q->h[i+1];
    }

    // set return value
    *_y = w[0] + _Complex_I*w[1];
}