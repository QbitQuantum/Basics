void kvz_eight_tap_filter_x8_and_flip(__m128i data01, __m128i data23, __m128i data45, __m128i data67, __m128i* filter, __m128i* dst)
{
    __m128i a, b, c, d;
    __m128i fir = _mm_broadcastq_epi64(_mm_loadl_epi64(filter));

    a = _mm_maddubs_epi16(data01, fir);
    b = _mm_maddubs_epi16(data23, fir);
    a = _mm_hadd_epi16(a, b);

    c = _mm_maddubs_epi16(data45, fir);
    d = _mm_maddubs_epi16(data67, fir);
    c = _mm_hadd_epi16(c, d);

    a = _mm_hadd_epi16(a, c);

    _mm_storeu_si128(dst, a);
}