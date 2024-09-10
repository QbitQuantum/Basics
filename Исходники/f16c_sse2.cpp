inline FORCE_INLINE __m128 mm_cvtph_ps(__m128i x)
{
	__m128 magic = _mm_castsi128_ps(_mm_set1_epi32((uint32_t)113 << 23));
	__m128i shift_exp = _mm_set1_epi32(0x7C00UL << 13);
	__m128i sign_mask = _mm_set1_epi32(0x8000U);
	__m128i mant_mask = _mm_set1_epi32(0x7FFF);
	__m128i exp_adjust = _mm_set1_epi32((127UL - 15UL) << 23);
	__m128i exp_adjust_nan = _mm_set1_epi32((127UL - 16UL) << 23);
	__m128i exp_adjust_denorm = _mm_set1_epi32(1UL << 23);
	__m128i zero = _mm_set1_epi16(0);

	__m128i exp, ret, ret_nan, ret_denorm, sign, mask0, mask1;

	x = _mm_unpacklo_epi16(x, zero);

	ret = _mm_and_si128(x, mant_mask);
	ret = _mm_slli_epi32(ret, 13);
	exp = _mm_and_si128(shift_exp, ret);
	ret = _mm_add_epi32(ret, exp_adjust);

	mask0 = _mm_cmpeq_epi32(exp, shift_exp);
	mask1 = _mm_cmpeq_epi32(exp, zero);

	ret_nan = _mm_add_epi32(ret, exp_adjust_nan);
	ret_denorm = _mm_add_epi32(ret, exp_adjust_denorm);
	ret_denorm = _mm_castps_si128(_mm_sub_ps(_mm_castsi128_ps(ret_denorm), magic));

	sign = _mm_and_si128(x, sign_mask);
	sign = _mm_slli_epi32(sign, 16);

	ret = mm_blendv_ps(ret_nan, ret, mask0);
	ret = mm_blendv_ps(ret_denorm, ret, mask1);

	ret = _mm_or_si128(ret, sign);
	return _mm_castsi128_ps(ret);
}