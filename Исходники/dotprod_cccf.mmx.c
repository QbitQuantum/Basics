// use MMX/SSE extensions
//
// (a + jb)(c + jd) = (ac - bd) + j(ad + bc)
//
// mm_x  = { x[0].real, x[0].imag, x[1].real, x[1].imag }
// mm_hi = { h[0].real, h[0].real, h[1].real, h[1].real }
// mm_hq = { h[0].imag, h[0].imag, h[1].imag, h[1].imag }
//
// mm_y0 = mm_x * mm_hi
//       = { x[0].real * h[0].real,
//           x[0].imag * h[0].real,
//           x[1].real * h[1].real,
//           x[1].imag * h[1].real };
//
// mm_y1 = mm_x * mm_hq
//       = { x[0].real * h[0].imag,
//           x[0].imag * h[0].imag,
//           x[1].real * h[1].imag,
//           x[1].imag * h[1].imag };
//
void dotprod_cccf_execute_mmx(dotprod_cccf _q,
                              float complex * _x,
                              float complex * _y)
{
    // type cast input as floating point array
    float * x = (float*) _x;

    // double effective length
    unsigned int n = 2*_q->n;

    // temporary buffers
    __m128 v;   // input vector
    __m128 hi;  // coefficients vector (real)
    __m128 hq;  // coefficients vector (imag)
    __m128 ci;  // output multiplication (v * hi)
    __m128 cq;  // output multiplication (v * hq)

    // aligned output array
    float w[4] __attribute__((aligned(16))) = {0,0,0,0};

#if HAVE_PMMINTRIN_H
    // SSE3
    __m128 s;   // dot product
    __m128 sum = _mm_setzero_ps(); // load zeros into sum register
#else
    // no SSE3
    float wi[4] __attribute__((aligned(16)));
    float wq[4] __attribute__((aligned(16)));
#endif

    // t = 4*(floor(_n/4))
    unsigned int t = (n >> 2) << 2;

    //
    unsigned int i;
    for (i=0; i<t; i+=4) {
        // load inputs into register (unaligned)
        // {x[0].real, x[0].imag, x[1].real, x[1].imag}
        v = _mm_loadu_ps(&x[i]);

        // load coefficients into register (aligned)
        hi = _mm_load_ps(&_q->hi[i]);
        hq = _mm_load_ps(&_q->hq[i]);

        // compute parallel multiplications
        ci = _mm_mul_ps(v, hi);
        cq = _mm_mul_ps(v, hq);

        // shuffle values
        cq = _mm_shuffle_ps( cq, cq, _MM_SHUFFLE(2,3,0,1) );
        
#if HAVE_PMMINTRIN_H
        // SSE3: combine using addsub_ps()
        s = _mm_addsub_ps( ci, cq );

        // accumulate
        sum = _mm_add_ps(sum, s);
#else
        // no SSE3: combine using slow method
        // FIXME: implement slow method
        // unload values
        _mm_store_ps(wi, ci);
        _mm_store_ps(wq, cq);

        // accumulate
        w[0] += wi[0] - wq[0];
        w[1] += wi[1] + wq[1];
        w[2] += wi[2] - wq[2];
        w[3] += wi[3] + wq[3];
#endif
    }

#if HAVE_PMMINTRIN_H
    // unload packed array
    _mm_store_ps(w, sum);
#endif

    // add in-phase and quadrature components
    w[0] += w[2];   // I
    w[1] += w[3];   // Q

    //float complex total = *((float complex*)w);
    float complex total = w[0] + w[1] * _Complex_I;

    // cleanup
    for (i=t/2; i<_q->n; i++)
        total += _x[i] * ( _q->hi[2*i] + _q->hq[2*i]*_Complex_I );

    // set return value
    *_y = total;
}