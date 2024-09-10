SSE_FUNCTION static void
add_f64_sse2_unroll (double *dest, double *src1, double *src2, int n)
{
    __m128d xmm0, xmm1;
    while (((long)dest & 15) && (0 < n)) {
        *dest++ = *src1++ + *src2++;
        n--;
    }
    while (3 < n) {
        xmm0 = _mm_loadu_pd(src1);
        xmm1 = _mm_loadu_pd(src2);
        xmm0 = _mm_add_pd(xmm0, xmm1);
        _mm_store_pd(dest, xmm0);

        xmm0 = _mm_loadu_pd(src1+2);
        xmm1 = _mm_loadu_pd(src2+2);
        xmm0 = _mm_add_pd(xmm0, xmm1);
        _mm_store_pd(dest+2, xmm0);
        dest += 4;
        src1 += 4;
        src2 += 4;
        n -= 4;
    }
    while (1 < n) {
        xmm0 = _mm_loadu_pd(src1);
        xmm1 = _mm_loadu_pd(src2);
        xmm0 = _mm_add_pd(xmm0, xmm1);
        _mm_store_pd(dest, xmm0);
        dest += 2;
        src1 += 2;
        src2 += 2;
        n -= 2;
    }
    while (0 < n) {
        *dest++ = *src1++ + *src2++;
        n--;
    }
}