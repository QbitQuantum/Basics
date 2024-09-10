inline __m128 SSENormalizeMultiplierSSE4(__m128 v)
{
	return _mm_rsqrt_ps(_mm_dp_ps(v, v, 0xFF));
}