void newviewGTRGAMMA_MIC(int tipCase,
                  double *x1, double *x2, double *x3, double *extEV, double *tipVector,
                  int *ex3, unsigned char *tipX1, unsigned char *tipX2,
                  int n, double *left, double *right, int *wgt, int *scalerIncrement, const pllBoolean fastScaling)
{
    __m512d minlikelihood_MIC = _mm512_set1_pd(PLL_MINLIKELIHOOD);
    __m512d twotothe256_MIC = _mm512_set1_pd(PLL_TWOTOTHE256);
    __m512i absMask_MIC = _mm512_set1_epi64(0x7fffffffffffffffULL);

	int addScale = 0;

    double aEV[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));

    #pragma ivdep
    for (int l = 0; l < 64; ++l)
    {
        aEV[l] = extEV[(l / 16) * 4 + (l % 4)];
    }

  switch(tipCase)
  {
    case PLL_TIP_TIP:
      {
        /* multiply all possible tip state vectors with the respective P-matrices
        */

            double umpX1[256] __attribute__((align(PLL_BYTE_ALIGNMENT)));
            double umpX2[256] __attribute__((align(PLL_BYTE_ALIGNMENT)));

            for(int k = 0; k < 256; ++k)
            {
                umpX1[k] = 0.0;
                umpX2[k] = 0.0;
            }

            for(int i = 0; i < maxStateValue; ++i)
            {
              for(int l = 0; l < states; ++l)
              {
                  #pragma ivdep
                  for(int k = 0; k < span; ++k)
                  {
                      umpX1[16 * i + k] +=  tipVector[i * 4 + l] *  left[k * 4 + l];
                      umpX2[16 * i + k] +=  tipVector[i * 4 + l] * right[k * 4 + l];
                  }
              }
            }

        double auX[64] __attribute__((align(64)));

        for(int i = 0; i < n; ++i)
        {
            _mm_prefetch((const char*) (const char*) &x3[span*(i+8)], _MM_HINT_ET1);
            _mm_prefetch((const char*) &x3[span*(i+8) + 8], _MM_HINT_ET1);

            _mm_prefetch((const char*) &x3[span*(i+1)], _MM_HINT_ET0);
            _mm_prefetch((const char*) &x3[span*(i+1) + 8], _MM_HINT_ET0);

            const double *uX1 = &umpX1[16 * tipX1[i]];
            const double *uX2 = &umpX2[16 * tipX2[i]];

            double uX[16] __attribute__((align(PLL_BYTE_ALIGNMENT)));
            double* v = &x3[i * 16];

            #pragma ivdep
            #pragma vector aligned
            for(int l = 0; l < 16; ++l)
            {
                uX[l] = uX1[l] * uX2[l];
                v[l] = 0.;
            }

            mic_broadcast16x64(uX, auX);

            for (int j = 0; j < 4; ++j)
            {
                #pragma ivdep
                #pragma vector aligned
                #pragma vector nontemporal
                for(int k = 0; k < 16; ++k)
                {
                    v[k] += auX[j*16 + k] * aEV[j*16 + k];
                }
            }

            // init scaling counter for the site
            if (!fastScaling)
                ex3[i] = 0;

        } // sites loop

      }
      break;
    case PLL_TIP_INNER:
      {
        /* we do analogous pre-computations as above, with the only difference that we now do them
        only for one tip vector */

          double umpX1[256] __attribute__((align(PLL_BYTE_ALIGNMENT)));

        /* precompute P and left tip vector product */

        for(int k = 0; k < 256; ++k)
        {
            umpX1[k] = 0.0;
        }

        for(int i = 0; i < 16; ++i)
        {
          for(int l = 0; l < 4; ++l)
          {
              #pragma ivdep
              for(int k = 0; k < 16; ++k)
              {
                  umpX1[16 * i + k] +=  tipVector[i * 4 + l] *  left[k * 4 + l];
              }
          }
        }

        // re-arrange right matrix for better memory layout
        double aRight[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));
        for(int j = 0; j < 4; j++)
        {
            for(int l = 0; l < 16; l++)
            {
                aRight[j*16 + l] = right[l*4 + j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            _mm_prefetch((const char*) &x2[span*(i+16)], _MM_HINT_T1);
            _mm_prefetch((const char*) &x2[span*(i+16) + 8], _MM_HINT_T1);
            _mm_prefetch((const char*) &x3[span*(i+16)], _MM_HINT_ET1);
            _mm_prefetch((const char*) &x3[span*(i+16) + 8], _MM_HINT_ET1);

            _mm_prefetch((const char*) &x2[span*(i+1)], _MM_HINT_T0);
            _mm_prefetch((const char*) &x2[span*(i+1) + 8], _MM_HINT_T0);
            _mm_prefetch((const char*) &x3[span*(i+1)], _MM_HINT_ET0);
            _mm_prefetch((const char*) &x3[span*(i+1) + 8], _MM_HINT_ET0);

            /* access pre-computed value based on the raw sequence data tipX1 that is used as an index */
            double* uX1 = &umpX1[span * tipX1[i]];
            double uX2[16] __attribute__((align(PLL_BYTE_ALIGNMENT)));
            double uX[16] __attribute__((align(PLL_BYTE_ALIGNMENT)));

            #pragma vector aligned
            for(int l = 0; l < 16; ++l)
            {
                uX2[l] = 0.;
            }

            double aV2[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));
            const double* v2 = &(x2[16 * i]);

            mic_broadcast16x64(v2, aV2);

            for(int j = 0; j < 4; j++)
            {
                #pragma ivdep
                #pragma vector aligned
                for(int l = 0; l < 16; l++)
                {
                    uX2[l] += aV2[j*16 + l] * aRight[j*16 + l];
                }
            }

            double* v3 = &(x3[span * i]);

            #pragma ivdep
            #pragma vector aligned
            for(int l = 0; l < 16; ++l)
            {
                uX[l] = uX1[l] * uX2[l];
                v3[l] = 0.;
            }

            double auX[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));
            mic_broadcast16x64(uX, auX);

            for (int j = 0; j < 4; ++j)
            {
                #pragma ivdep
                #pragma vector aligned
                for(int k = 0; k < 16; ++k)
                {
                    v3[k] += auX[j*16 + k] * aEV[j*16 + k];
                }
            }

            __m512d t1 = _mm512_load_pd(&v3[0]);
            t1 = _mm512_castsi512_pd(_mm512_and_epi64(_mm512_castpd_si512(t1), absMask_MIC));
            double vmax1 = _mm512_reduce_gmax_pd(t1);
            __m512d t2 = _mm512_load_pd(&v3[8]);
            t2 = _mm512_castsi512_pd(_mm512_and_epi64(_mm512_castpd_si512(t2), absMask_MIC));
            double vmax2 = _mm512_reduce_gmax_pd(t2);

            if(vmax1 < PLL_MINLIKELIHOOD && vmax2 < PLL_MINLIKELIHOOD)
            {
				t1 = _mm512_mul_pd(t1, twotothe256_MIC);
				_mm512_store_pd(&v3[0], t1);
				t2 = _mm512_mul_pd(t2, twotothe256_MIC);
				_mm512_store_pd(&v3[8], t2);

                if(!fastScaling)
                  ex3[i] += 1;
                else
                  addScale += wgt[i];
            }
        } // site loop
      }
      break;
    case PLL_INNER_INNER:
    {
      /* same as above, without pre-computations */

        // re-arrange right matrix for better memory layout
        double aLeft[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));
        double aRight[64] __attribute__((align(PLL_BYTE_ALIGNMENT)));
        for(int j = 0; j < 4; j++)
        {
            for(int l = 0; l < 16; l++)
            {
                aLeft[j*16 + l] = left[l*4 + j];
                aRight[j*16 + l] = right[l*4 + j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            _mm_prefetch((const char*) &x1[span*(i+8)], _MM_HINT_T1);
            _mm_prefetch((const char*) &x1[span*(i+8) + 8], _MM_HINT_T1);
            _mm_prefetch((const char*) &x2[span*(i+8)], _MM_HINT_T1);
            _mm_prefetch((const char*) &x2[span*(i+8) + 8], _MM_HINT_T1);
            _mm_prefetch((const char*) &x3[span*(i+8)], _MM_HINT_ET1);
            _mm_prefetch((const char*) &x3[span*(i+8) + 8], _MM_HINT_ET1);

            _mm_prefetch((const char*) &x1[span*(i+1)], _MM_HINT_T0);
            _mm_prefetch((const char*) &x1[span*(i+1) + 8], _MM_HINT_T0);
            _mm_prefetch((const char*) &x2[span*(i+1)], _MM_HINT_T0);
            _mm_prefetch((const char*) &x2[span*(i+1) + 8], _MM_HINT_T0);
            _mm_prefetch((const char*) &x3[span*(i+1)], _MM_HINT_ET0);
            _mm_prefetch((const char*) &x3[span*(i+1) + 8], _MM_HINT_ET0);

            double uX1[16] __attribute__((align(64)));
            double uX2[16] __attribute__((align(64)));
            double uX[16] __attribute__((align(64)));

            for(int l = 0; l < 16; l++)
            {
              uX1[l] = 0.;
              uX2[l] = 0.;
            }

            double aV1[64] __attribute__((align(64)));
            double aV2[64] __attribute__((align(64)));

            const double* v1 = &(x1[span * i]);
            const double* v2 = &(x2[span * i]);

            mic_broadcast16x64(v1, aV1);

            mic_broadcast16x64(v2, aV2);

            for(int j = 0; j < 4; j++)
            {
                #pragma ivdep
                #pragma vector aligned
                for(int l = 0; l < 16; l++)
                {
                    uX1[l] += aV1[j*16 + l] * aLeft[j*16 + l];
                    uX2[l] += aV2[j*16 + l] * aRight[j*16 + l];
                }
            }

            double* v3 =  &(x3[span * i]);

            #pragma ivdep
            #pragma vector aligned
            for(int l = 0; l < 16; ++l)
            {
                uX[l] = uX1[l] * uX2[l];
                v3[l] = 0.;
            }

            double auX[64] __attribute__((align(64)));
            mic_broadcast16x64(uX, auX);

            for(int j = 0; j < 4; ++j)
            {
                #pragma ivdep
                #pragma vector aligned
                for(int k = 0; k < 16; ++k)
                {
                    v3[k] += auX[j*16 + k] * aEV[j*16 + k];
                }
            }


            __m512d t1 = _mm512_load_pd(&v3[0]);
            t1 = _mm512_castsi512_pd(_mm512_and_epi64(_mm512_castpd_si512(t1), absMask_MIC));
            double vmax1 = _mm512_reduce_gmax_pd(t1);
            __m512d t2 = _mm512_load_pd(&v3[8]);
            t2 = _mm512_castsi512_pd(_mm512_and_epi64(_mm512_castpd_si512(t2), absMask_MIC));
            double vmax2 = _mm512_reduce_gmax_pd(t2);

            if(vmax1 < PLL_MINLIKELIHOOD && vmax2 < PLL_MINLIKELIHOOD)
            {
				t1 = _mm512_mul_pd(t1, twotothe256_MIC);
				_mm512_store_pd(&v3[0], t1);
				t2 = _mm512_mul_pd(t2, twotothe256_MIC);
				_mm512_store_pd(&v3[8], t2);

                if(!fastScaling)
                  ex3[i] += 1;
                else
                  addScale += wgt[i];
            }
        }
    } break;
    default:
//      assert(0);
      break;
  }

  /* as above, increment the global counter that counts scaling multiplications by the scaling multiplications
     carried out for computing the likelihood array at node p */

  if (fastScaling)
  {
      *scalerIncrement = addScale;
  }

}