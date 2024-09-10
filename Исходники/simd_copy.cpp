void simd_memcpy(void *dst, void *src, size_t nbytes)
{
    size_t i;

    size_t ilen = nbytes/sizeof(int);
    size_t ilen_sm = ilen - ilen%16;

    char *cdst=(char*)dst;
    char *csrc=(char*)src;

    int * idst=(int*)dst;
    int * isrc=(int*)src;

    __m128i l0,l1,l2,l3;

    _mm_prefetch((__m128i*)&isrc[0], _MM_HINT_NTA);
    _mm_prefetch((__m128i*)&isrc[4], _MM_HINT_NTA);
    _mm_prefetch((__m128i*)&isrc[8], _MM_HINT_NTA);
    _mm_prefetch((__m128i*)&isrc[12], _MM_HINT_NTA);

    for(i=0; i<ilen_sm; i+=16)
    {
        l0 =  _mm_load_si128((__m128i*)&isrc[i+0]);
        l1 =  _mm_load_si128((__m128i*)&isrc[i+4]);
        l2 =  _mm_load_si128((__m128i*)&isrc[i+8]);
        l3 =  _mm_load_si128((__m128i*)&isrc[i+12]);

        _mm_prefetch((__m128i*)&isrc[i+16], _MM_HINT_NTA);
        _mm_prefetch((__m128i*)&isrc[i+20], _MM_HINT_NTA);
        _mm_prefetch((__m128i*)&isrc[i+24], _MM_HINT_NTA);
        _mm_prefetch((__m128i*)&isrc[i+28], _MM_HINT_NTA);

        _mm_stream_si128((__m128i*)&idst[i+0],  l0);
        _mm_stream_si128((__m128i*)&idst[i+4],  l1);
        _mm_stream_si128((__m128i*)&idst[i+8],  l2);
        _mm_stream_si128((__m128i*)&idst[i+12], l3);

    }

    for(i=ilen_sm; i<ilen; i++)
    {
        idst[i] = isrc[i];
    }

    for(i=(4*ilen); i<nbytes; i++)
    {
        cdst[i] = csrc[i];
    }
}