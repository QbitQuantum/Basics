// useful for debugging
inline bool equal128(__m128i x, __m128i y)
{
    return ((_mm_extract_epi32(x,0) == _mm_extract_epi32(y,0)) &&
	    (_mm_extract_epi32(x,1) == _mm_extract_epi32(y,1)) &&
	    (_mm_extract_epi32(x,2) == _mm_extract_epi32(y,2)) &&
	    (_mm_extract_epi32(x,3) == _mm_extract_epi32(y,3)));
}