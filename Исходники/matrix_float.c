void	matrix_CpAAt_float (float* C,const float* A,size_t n,size_t p)
{
    size_t i,j,k;
    size_t q = n / 8;
    size_t r = n % 8;

    for (k=0;k<p;k++) {
        float* pC = C;
        for (j=0;j<n;j++) {
            __m128 w = _mm_load1_ps (A+j+k*n);
            const float* pA = A+k*n;
            if (ALGEBRA_IS_ALIGNED(pA) && ALGEBRA_IS_ALIGNED(pC)) {
                for (i=0;i<q;i++) {
                    __m128 i1 = _mm_load_ps(pA);
                    __m128 i2 = _mm_load_ps(pA+4);
                    __m128 o1 = _mm_load_ps(pC);
                    __m128 o2 = _mm_load_ps(pC+4);
                    _mm_store_ps(pC+0,_mm_add_ps(o1,_mm_mul_ps(i1,w)));
                    _mm_store_ps(pC+4,_mm_add_ps(o2,_mm_mul_ps(i2,w)));
                    pA += 8;
                    pC += 8;
                }
            }
            else {
                for (i=0;i<q;i++) {
                    __m128 i1 = _mm_loadu_ps(pA);
                    __m128 i2 = _mm_loadu_ps(pA+4);
                    __m128 o1 = _mm_loadu_ps(pC);
                    __m128 o2 = _mm_loadu_ps(pC+4);
                    _mm_storeu_ps(pC+0,_mm_add_ps(o1,_mm_mul_ps(i1,w)));
                    _mm_storeu_ps(pC+4,_mm_add_ps(o2,_mm_mul_ps(i2,w)));
                    pA += 8;
                    pC += 8;
                }
            }
            for (i=0;i<r;i++) {
                (*pC++) += A[j+k*n]*(*pA++);
            }
        }
    }
}