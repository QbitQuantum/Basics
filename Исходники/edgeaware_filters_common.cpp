void mad(register float *dst, register float *src1, float alpha, float beta, int w)
{
    register int j = 0;
#if CV_SSE
    if (CPU_SUPPORT_SSE1)
    {
        __m128 a, b, c;
        a = _mm_set_ps1(alpha);
        b = _mm_set_ps1(beta);
        for (; j < w - 3; j += 4)
        {
            c = _mm_loadu_ps(src1 + j);
            c = _mm_mul_ps(c, a);
            c = _mm_add_ps(c, b);
            _mm_storeu_ps(dst + j, c);
        }
    }
#endif
    for (; j < w; j++)
        dst[j] = alpha*src1[j] + beta;
}