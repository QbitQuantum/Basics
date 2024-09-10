static inline void computeVectorGTRGAMMAPROT(double *lVector, int *eVector, double *gammaRates, int i, double qz, double rz,
        traversalInfo *ti, double *EIGN, double *EI, double *EV, double *tipVector,
        unsigned  char **yVector, int mxtips)
{
    double
    *x1,
    *x2,
    *x3;

    int
    s,
    pNumber = ti->pNumber,
    rNumber = ti->rNumber,
    qNumber = ti->qNumber,
    index1[4],
    index2[4];


    x3  = &(lVector[80 * (pNumber  - mxtips)]);

    switch(ti->tipCase)
    {
    case TIP_TIP:
        x1 = &(tipVector[20 * yVector[qNumber][i]]);
        x2 = &(tipVector[20 * yVector[rNumber][i]]);
        for(s = 0; s < 4; s++)
        {
            index1[s] = 0;
            index2[s] = 0;
        }
        break;
    case TIP_INNER:
        x1 = &(tipVector[20 * yVector[qNumber][i]]);
        x2 = &(  lVector[80 * (rNumber - mxtips)]);
        for(s = 0; s < 4; s++)
            index1[s] = 0;
        for(s = 0; s < 4; s++)
            index2[s] = s;
        break;
    case INNER_INNER:
        x1 = &(lVector[80 * (qNumber - mxtips)]);
        x2 = &(lVector[80 * (rNumber - mxtips)]);
        for(s = 0; s < 4; s++)
        {
            index1[s] = s;
            index2[s] = s;
        }
        break;
    default:
        assert(0);
    }

    {
        double
        e1[20] __attribute__ ((aligned (BYTE_ALIGNMENT))),
        e2[20] __attribute__ ((aligned (BYTE_ALIGNMENT))),
        d1[20] __attribute__ ((aligned (BYTE_ALIGNMENT))),
        d2[20] __attribute__ ((aligned (BYTE_ALIGNMENT))),
        lz1, lz2;

        int
        l,
        k,
        scale,
        j;

        for(j = 0; j < 4; j++)
        {
            lz1 = qz * gammaRates[j];
            lz2 = rz * gammaRates[j];

            e1[0] = 1.0;
            e2[0] = 1.0;

            for(l = 1; l < 20; l++)
            {
                e1[l] = EXP(EIGN[l] * lz1);
                e2[l] = EXP(EIGN[l] * lz2);
            }

            for(l = 0; l < 20; l+=2)
            {
                __m128d d1v = _mm_mul_pd(_mm_load_pd(&x1[20 * index1[j] + l]), _mm_load_pd(&e1[l]));
                __m128d d2v = _mm_mul_pd(_mm_load_pd(&x2[20 * index2[j] + l]), _mm_load_pd(&e2[l]));

                _mm_store_pd(&d1[l], d1v);
                _mm_store_pd(&d2[l], d2v);
            }

            __m128d zero = _mm_setzero_pd();

            for(l = 0; l < 20; l+=2)
                _mm_store_pd(&x3[j * 20 + l], zero);

            for(l = 0; l < 20; l++)
            {
                double *ev = &EV[l * 20];
                __m128d ump_x1v = _mm_setzero_pd();
                __m128d ump_x2v = _mm_setzero_pd();
                __m128d x1px2v;

                for(k = 0; k < 20; k+=2)
                {
                    __m128d eiv = _mm_load_pd(&EI[20 * l + k]);
                    __m128d d1v = _mm_load_pd(&d1[k]);
                    __m128d d2v = _mm_load_pd(&d2[k]);
                    ump_x1v = _mm_add_pd(ump_x1v, _mm_mul_pd(d1v, eiv));
                    ump_x2v = _mm_add_pd(ump_x2v, _mm_mul_pd(d2v, eiv));
                }

                ump_x1v = _mm_hadd_pd(ump_x1v, ump_x1v);
                ump_x2v = _mm_hadd_pd(ump_x2v, ump_x2v);

                x1px2v = _mm_mul_pd(ump_x1v, ump_x2v);

                for(k = 0; k < 20; k+=2)
                {
                    __m128d ex3v = _mm_load_pd(&x3[j * 20 + k]);
                    __m128d EVV  = _mm_load_pd(&ev[k]);
                    ex3v = _mm_add_pd(ex3v, _mm_mul_pd(x1px2v, EVV));

                    _mm_store_pd(&x3[j * 20 + k], ex3v);
                }
            }
        }

        scale = 1;
        for(l = 0; scale && (l < 80); l++)
            scale = ((x3[l] < minlikelihood) && (x3[l] > minusminlikelihood));

        if(scale)
        {
            __m128d twoto = _mm_set_pd(twotothe256, twotothe256);

            for(l = 0; l < 80; l+=2)
            {
                __m128d ex3v = _mm_mul_pd(_mm_load_pd(&x3[l]),twoto);
                _mm_store_pd(&x3[l], ex3v);
            }

            *eVector = *eVector + 1;
        }

        return;
    }
}