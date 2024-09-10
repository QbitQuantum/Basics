int test()
{
    const float src[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    short dst[8];
    __m128 v_src = _mm_load_ps(src);
    __m128i v_dst = _mm_cvtps_ph(v_src, 0);
    _mm_storel_epi64((__m128i*)dst, v_dst);
    return (int)dst[0];
}