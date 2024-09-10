int RowVec_32f_AVX(const float* src0, const float* _kx, float* dst, int width, int cn, int _ksize)
{
    int i = 0, k;
    for (; i <= width - 8; i += 8)
    {
        const float* src = src0 + i;
        __m256 f, x0;
        __m256 s0 = _mm256_set1_ps(0.0f);
        for (k = 0; k < _ksize; k++, src += cn)
        {
            f = _mm256_set1_ps(_kx[k]);
            x0 = _mm256_loadu_ps(src);
#if CV_FMA3
            s0 = _mm256_fmadd_ps(x0, f, s0);
#else
            s0 = _mm256_add_ps(s0, _mm256_mul_ps(x0, f));
#endif
        }
        _mm256_storeu_ps(dst + i, s0);
    }
    _mm256_zeroupper();
    return i;
}