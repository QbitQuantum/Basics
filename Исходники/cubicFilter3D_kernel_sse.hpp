inline float dot_product(__m128 a, __m128 b)
{
#if defined(SSE4)
	__m128 m = _mm_dp_ps(a, b, 0xff);
	return m.m128_f32[0];
#elif defined(SSE3)
	__m128 m = _mm_mul_ps(a, b);
	m = _mm_hadd_ps(m, m);
	m = _mm_hadd_ps(m, m);
	return m.m128_f32[0];
#else
	__m128 m = _mm_mul_ps(a, b);
	return m.m128_f32[0] + m.m128_f32[1] + m.m128_f32[2] + m.m128_f32[3];
#endif
}