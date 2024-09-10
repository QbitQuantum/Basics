void transpose_aligned(double *a, double *b, int N1, int N2, double factor) {

    int i,j,k,k1,it,jt,itt,jtt,conflict,tmp,tmpN;
    double *pA, *pB;


    register __m128d x, y, z, w,fac_vector;

    fac_vector = _mm_load_sd(&factor);
    fac_vector = _mm_unpacklo_pd(fac_vector,fac_vector);

    for (it = 0; it < N1; it=it+tilesize) {
        for (jt = 0; jt < N2; jt=jt+tilesize) {

            k = 0;
            for (j = jt; j < jt+tilesize; j=j+2) {
                for (i = it; i < it+tilesize; i=i+2) {
                    pA = a+i*N2+j;
                    x = _mm_load_pd(pA);
                    y = _mm_load_pd(pA + N2);
                    x = _mm_mul_pd(x,fac_vector);
                    y = _mm_mul_pd(y,fac_vector);
                    z = _mm_shuffle_pd( x, y, 0);
                    w = _mm_shuffle_pd( x, y, 3);
                    k = (j-jt)*tilesize + (i-it);
                    _mm_store_pd(buf + k,z);
                    _mm_store_pd(buf + k + tilesize,w);
                }
            }

            k = 0;
            k1 = 0;
            for (j = jt; j < jt+tilesize; j++) {
                pB = b+j*N1+it;
                k = (j-jt)*tilesize;
                x = _mm_load_pd(&buf[k]);
                y = _mm_load_pd(&buf[k]+2);
                z = _mm_load_pd(&buf[k]+2*2);
                w = _mm_load_pd(&buf[k]+3*2);
                _mm_stream_pd(pB,x);
                _mm_stream_pd(pB+2,y);
                _mm_stream_pd(pB+2*2,z);
                _mm_stream_pd(pB+3*2,w);

            }
        }
    }
}