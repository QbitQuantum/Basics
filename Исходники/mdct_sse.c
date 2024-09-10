static void
mdct_bitreverse_sse(MDCTContext *mdct, FLOAT *x)
{
    int        n   = mdct->n;
    int       *bit = mdct->bitrev;
    float *w0      = x;
    float *w1      = x = w0+(n>>1);
    float *T       = mdct->trig_bitreverse;

    do {
        float *x0    = x+bit[0];
        float *x1    = x+bit[1];
        float *x2    = x+bit[2];
        float *x3    = x+bit[3];

        __m128  XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7;
        w1       -= 4;

        XMM0     = _mm_lddqu_ps(x0);
        XMM1     = _mm_lddqu_ps(x1);
        XMM4     = _mm_lddqu_ps(x2);
        XMM7     = _mm_lddqu_ps(x3);
        XMM2     = XMM0;
        XMM3     = XMM1;
        XMM5     = XMM0;
        XMM6     = XMM1;

        XMM0     = _mm_shuffle_ps(XMM0, XMM4, _MM_SHUFFLE(0,1,0,1));
        XMM1     = _mm_shuffle_ps(XMM1, XMM7, _MM_SHUFFLE(0,1,0,1));
        XMM2     = _mm_shuffle_ps(XMM2, XMM4, _MM_SHUFFLE(0,0,0,0));
        XMM3     = _mm_shuffle_ps(XMM3, XMM7, _MM_SHUFFLE(0,0,0,0));
        XMM5     = _mm_shuffle_ps(XMM5, XMM4, _MM_SHUFFLE(1,1,1,1));
        XMM6     = _mm_shuffle_ps(XMM6, XMM7, _MM_SHUFFLE(1,1,1,1));
        XMM4     = _mm_load_ps(T  );
        XMM7     = _mm_load_ps(T+4);

        XMM1     = _mm_xor_ps(XMM1, PCS_RNRN.v);
        XMM2     = _mm_add_ps(XMM2, XMM3);
        XMM5     = _mm_sub_ps(XMM5, XMM6);

        XMM0     = _mm_add_ps(XMM0, XMM1);
        XMM2     = _mm_mul_ps(XMM2, XMM4);
        XMM5     = _mm_mul_ps(XMM5, XMM7);

        XMM0     = _mm_mul_ps(XMM0, PFV_0P5.v);
        XMM2     = _mm_add_ps(XMM2, XMM5);

        XMM1     = XMM0;
        XMM3     = XMM2;

        XMM1     = _mm_xor_ps(XMM1, PCS_RNRN.v);
        XMM3     = _mm_xor_ps(XMM3, PCS_RNRN.v);

        XMM0     = _mm_add_ps(XMM0, XMM2);
        XMM1     = _mm_sub_ps(XMM1, XMM3);

        _mm_store_ps(w0, XMM0);
        _mm_storeh_pi((__m64*)(w1  ), XMM1);
        _mm_storel_pi((__m64*)(w1+2), XMM1);

        T       += 8;
        bit     += 4;
        w0      += 4;
    } while (w0 < w1);
}