static inline void
transpose_sse (gfloat *src, gfloat *dst, const int width, const int height)
{
    __m128 row1 = _mm_loadu_ps (src);
    __m128 row2 = _mm_loadu_ps (src + height);
    __m128 row3 = _mm_loadu_ps (src + 2 * height);
    __m128 row4 = _mm_loadu_ps (src + 3 * height);
    _MM_TRANSPOSE4_PS (row1, row2, row3, row4);
    _mm_storeu_ps (dst, row1);
    _mm_storeu_ps (dst + width, row2);
    _mm_storeu_ps (dst + 2 * width, row3);
    _mm_storeu_ps (dst + 3 * width, row4);
}