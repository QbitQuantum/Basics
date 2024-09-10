static inline __m128 
log2f4(__m128 x)
{
	__m128i exp = _mm_load_si128((__m128i*)_exp_mask);
	__m128i mant = _mm_load_si128((__m128i*)_mantissa_mask);
	__m128 one = _mm_load_ps(_ones_ps);
	__m128i i = _mm_castps_si128(x);
	__m128 e = _mm_cvtepi32_ps(_mm_sub_epi32(_mm_srli_epi32(_mm_and_si128(i, exp), 23), _mm_load_si128((__m128i*)_one27)));
	__m128 m = _mm_or_ps(_mm_castsi128_ps(_mm_and_si128(i, mant)), one);
	__m128 p;

	/* Minimax polynomial fit of log2(x)/(x - 1), for x in range [1, 2[ */
#if LOG_POLY_DEGREE == 6
	p = POLY5( m, log_p5_0, log_p5_1, log_p5_2, log_p5_3, log_p5_4, log_p5_5);
#elif LOG_POLY_DEGREE == 5
	p = POLY4(m, log_p4_0, log_p4_1, log_p4_2, log_p4_3, log_p4_4);
#elif LOG_POLY_DEGREE == 4
	p = POLY3(m, log_p3_0, log_p3_1, log_p3_2, log_p3_3);
#elif LOG_POLY_DEGREE == 3
	p = POLY2(m, log_p2_0, log_p2_1, log_p2_2);
#else
#error
#endif

	/* This effectively increases the polynomial degree by one, but ensures that log2(1) == 0*/
	p = _mm_mul_ps(p, _mm_sub_ps(m, one));

	return _mm_add_ps(p, e);
}