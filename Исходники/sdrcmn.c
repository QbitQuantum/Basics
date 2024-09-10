/* dot products: d1={dot(a1,b1),dot(a1,b2)},d2={dot(a2,b1),dot(a2,b2)} ---------
* args   : short  *a1       I   input short array
*          short  *a2       I   input short array
*          short  *b1       I   input short array
*          short  *b2       I   input short array
*          int    n         I   number of input data
*          short  *d1       O   output short array
*          short  *d2       O   output short array
* return : none
*-----------------------------------------------------------------------------*/
extern void dot_22(const short *a1, const short *a2, const short *b1,
                   const short *b2, int n, double *d1, double *d2)
{
    const short *p1=a1,*p2=a2,*q1=b1,*q2=b2;

#if defined(AVX2_ENABLE)
    __m256i xmm1,xmm2,xmm3,xmm4;

    n=16*(int)ceil((double)n/16); /* modification to multiples of 16 */
    xmm1=_mm256_setzero_si256();
    xmm2=_mm256_setzero_si256();
    xmm3=_mm256_setzero_si256();
    xmm4=_mm256_setzero_si256();

    for (;p1<a1+n;p1+=16,p2+=16,q1+=16,q2+=16) {
        MULADD_INT16_AVX(xmm1,p1,q1);
        MULADD_INT16_AVX(xmm2,p1,q2);
        MULADD_INT16_AVX(xmm3,p2,q1);
        MULADD_INT16_AVX(xmm4,p2,q2);
    }
    SUM_INT32_AVX(d1[0],xmm1);
    SUM_INT32_AVX(d1[1],xmm2);
    SUM_INT32_AVX(d2[0],xmm3);
    SUM_INT32_AVX(d2[1],xmm4);

#elif defined(SSE2_ENABLE)
    __m128i xmm1,xmm2,xmm3,xmm4;

    n=8*(int)ceil((double)n/8); /* modification to multiples of 8 */
    xmm1=_mm_setzero_si128();
    xmm2=_mm_setzero_si128();
    xmm3=_mm_setzero_si128();
    xmm4=_mm_setzero_si128();

    for (;p1<a1+n;p1+=8,p2+=8,q1+=8,q2+=8) {
        MULADD_INT16(xmm1,p1,q1);
        MULADD_INT16(xmm2,p1,q2);
        MULADD_INT16(xmm3,p2,q1);
        MULADD_INT16(xmm4,p2,q2);
    }
    SUM_INT32(d1[0],xmm1);
    SUM_INT32(d1[1],xmm2);
    SUM_INT32(d2[0],xmm3);
    SUM_INT32(d2[1],xmm4);

#else
    d1[0]=d1[1]=d2[0]=d2[1]=0.0;

    for (;p1<a1+n;p1++,p2++,q1++,q2++) {
        d1[0]+=(*p1)*(*q1);
        d1[1]+=(*p1)*(*q2);
        d2[0]+=(*p2)*(*q1);
        d2[1]+=(*p2)*(*q2);
    }
#endif
}