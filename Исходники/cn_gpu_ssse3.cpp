inline void prep_dv(__m128i* idx, __m128i& v, __m128& n)
{
    v = _mm_load_si128(idx);
    n = _mm_cvtepi32_ps(v);
}