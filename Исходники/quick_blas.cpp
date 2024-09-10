        void dcopy(unsigned int N, const double* x, double* y) {
#ifdef GX_SSE
            if(SSE2_supported) {
                __m128d X1,X2 ;
                unsigned int i = 0 ;
                while(i<N) {
                    _mm_prefetch((const char*)(&y[i] + 128), _MM_HINT_NTA) ;
                    X1 = _mm_load_pd(&x[i]) ;
                    i+=2 ;
                    X2 = _mm_load_pd(&x[i]) ;
                    i+=2 ;
                    _mm_stream_pd(&y[i - 4], X1) ;
                    _mm_stream_pd(&y[i - 2], X2) ;
                }
                _mm_sfence() ;
                return ;
            }
#endif
            memcpy(y, x, N * sizeof(double)) ;
        }