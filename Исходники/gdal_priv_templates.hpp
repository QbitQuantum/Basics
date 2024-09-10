inline void GDALCopy2WordsSSE(const float* pValueIn, Tout* const &pValueOut)
{
    float fMaxVal, fMinVal;
    GDALGetDataLimits<float, Tout>(fMaxVal, fMinVal);
    __m128 xmm = _mm_set_ps(0, 0, pValueIn[1], pValueIn[0]);
    __m128 xmm_min = _mm_set_ps(0, 0, fMinVal, fMinVal);
    __m128 xmm_max = _mm_set_ps(0, 0, fMaxVal, fMaxVal);
    xmm = _mm_min_ps(_mm_max_ps(xmm, xmm_min), xmm_max);
    pValueOut[0] = _mm_cvtss_si32(xmm);
    pValueOut[1] = _mm_cvtss_si32(_mm_shuffle_ps(xmm, xmm, _MM_SHUFFLE(0, 0, 0, 1)));
}