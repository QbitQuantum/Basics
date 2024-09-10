void mBior53::synthcols(char** dest, char** sour, unsigned int w, unsigned int h) const     //w,h of the LO part
{
        float fz = 0.0f;
        float mul2 = 2.0f;

        int n;
        float s2k, s2k1;
        __m128 ms2k, ms2k1;
        unsigned int w2 = 2 * w;

        const vec1D& H2m = getH2m();
        const vec1D& G2m = getG2m();
        const vec1D& H2m1 = getH2m1();
        const vec1D& G2m1 = getG2m1();

        for (unsigned int x = 0; x < w2 / 4; x++) {      //x<w2/2   x = 4*x
                for (unsigned int k = 0; k < h; k++) {

                        ms2k = _mm_load_ss(&fz);
                        ms2k1 = ms2k;

                        for (int m = 0; m <= 0; m++) {                             //s2k even H
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                ms2k = _mm_add_ps(ms2k, _mm_mul_ps(_mm_load_ps1(H2m.data(m)), _mm_cvtpi8_ps(*(__m64 *)(&sour[n][4*x]))));
                        }
                        for (int m = 0; m <= 1; m++) {                             //s2k even G
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                ms2k = _mm_add_ps(ms2k, _mm_mul_ps(_mm_load_ps1(G2m.data(m)), _mm_cvtpi8_ps(*(__m64 *)(&sour[n+h][4*x]))));
                        }

                        for (int m = -1; m <= 0; m++) {                           //s2k1 odd H
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                ms2k1 = _mm_add_ps(ms2k1, _mm_mul_ps(_mm_load_ps1(H2m1.data(m)), _mm_cvtpi8_ps(*(__m64 *)(&sour[n][4*x]))));
                        }
                        for (int m = -1; m <= 1; m++) {                          //s2k1 odd G
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                ms2k1 = _mm_add_ps(ms2k1, _mm_mul_ps(_mm_load_ps1(G2m1.data(m)), _mm_cvtpi8_ps(*(__m64 *)(&sour[n+h][4*x]))));
                        }

                        __m128 mmul2 = _mm_load_ps1(&mul2);

                        mmxround4(&dest[2*k][4*x], _mm_mul_ps(ms2k, mmul2));
                        mmxround4(&dest[2*k+1][4*x], _mm_mul_ps(ms2k1, mmul2));
                }
        }
        _mm_empty();


        //odd remainder
        for (unsigned int x = w2 - (w2 % 4); x < w2; x++) {
                for (unsigned int k = 0; k < h; k++) {

                        s2k = 0;
                        s2k1 = 0;

                        for (int m = H2m.first(); m <= H2m.last(); m++) {        //s2k even H
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                s2k += H2m[m] * float(sour[n][x]);
                        }
                        for (int m = G2m.first(); m <= G2m.last(); m++) {        //s2k even G
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                s2k += G2m[m] * float(sour[n+h][x]);
                        }

                        for (int m = H2m1.first(); m <= H2m1.last(); m++) {     //s2k1 odd H
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                s2k1 += H2m1[m] * float(sour[n][x]);
                        }
                        for (int m = G2m1.first(); m <= G2m1.last(); m++) {      //s2k1 odd G
                                n = k - m;
                                if (n < 0) n = 0 - n;
                                if (n >= (int)h) n -= 2 * (1 + n - h);
                                s2k1 += G2m1[m] * float(sour[n+h][x]);
                        }

                        dest[2*k][x] = mmxround(2.0f * s2k);
                        dest[2*k+1][x] = mmxround(2.0f * s2k1);
                }
        }
}