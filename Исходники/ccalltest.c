JL_DLLEXPORT __m128i test_m128i(__m128i a, __m128i b, __m128i c, __m128i d)
{
    // 64-bit x86 has only level 2 SSE, which does not have a <4 x int32> multiplication,
    // so we use floating-point instead, and assume caller knows about the hack.
    return _mm_add_epi32(a,
                         _mm_cvtps_epi32(_mm_mul_ps(_mm_cvtepi32_ps(b),
                                                    _mm_cvtepi32_ps(_mm_sub_epi32(c,d)))));
}