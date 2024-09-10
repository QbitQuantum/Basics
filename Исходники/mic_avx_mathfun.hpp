// sin()
static inline mic_m512_t mic_sin_ps(mic_m512_t x) {
	__m512i sign_bit;
	sign_bit = _mm512_and_epi32(_mm512_castps_si512(x), _pi32_sign_mask);
	x = _mm512_castsi512_ps(_mm512_and_epi32(_mm512_castps_si512(x), _pi32_inv_sign_mask));
	
	mic_m512_t y = _mm512_mul_ps(x, _ps_cephes_FOPI);

	__m512i emm2 = _mm512_cvtfxpnt_round_adjustps_epi32(y, _MM_FROUND_TO_NEAREST_INT, _MM_EXPADJ_NONE);
	emm2 = _mm512_add_epi32(emm2, _pi32_1);
	emm2 = _mm512_and_epi32(emm2, _pi32_inv1);
	y = _mm512_cvtfxpnt_round_adjustepu32_ps(emm2, _MM_FROUND_TO_NEAREST_INT, _MM_EXPADJ_NONE);

	__m512i emm0 = _mm512_and_epi32(emm2, _pi32_4);
	emm0 = _mm512_slli_epi32(emm0, 29);

	emm2 = _mm512_and_epi32(emm2, _pi32_2);
	__mmask16 mask = _mm512_cmp_epi32_mask(emm2, _pi32_0, _MM_CMPINT_EQ);
	emm2 = _mm512_mask_add_epi32(_pi32_0, mask, _pi32_ffff, _pi32_0);
	
	sign_bit = _mm512_xor_epi32(sign_bit, emm0);
	
	mic_m512_t temp = _ps_minus_cephes_DP123;
	temp = _mm512_mul_ps(y, temp);
	x = _mm512_add_ps(x, temp);

	mic_m512_t x2 = _mm512_mul_ps(x, x);
	mic_m512_t x3 = _mm512_mul_ps(x2, x);
	mic_m512_t x4 = _mm512_mul_ps(x2, x2);

	y = _mm512_mul_ps(_ps_coscof_p0, x2);
	mic_m512_t y2 = _mm512_mul_ps(_ps_sincof_p0, x2);
	y = _mm512_add_ps(y, _ps_coscof_p1);
	y2 = _mm512_add_ps(y2, _ps_sincof_p1);
	y = _mm512_mul_ps(y, x2);
	y2 = _mm512_mul_ps(y2, x2);
	y = _mm512_add_ps(y, _ps_coscof_p2);
	y2 = _mm512_add_ps(y2, _ps_sincof_p2);
	y = _mm512_mul_ps(y, x4);
	y2 = _mm512_mul_ps(y2, x3);
	temp = _mm512_mul_ps(x2, _ps_0point5);
	temp = _mm512_sub_ps(temp, _ps_1);
	y = _mm512_sub_ps(y, temp);
	y2 = _mm512_add_ps(y2, x);

	y = _mm512_castsi512_ps(_mm512_andnot_epi32(emm2, _mm512_castps_si512(y)));
	y2 = _mm512_castsi512_ps(_mm512_and_epi32(emm2, _mm512_castps_si512(y2)));

	y = _mm512_add_ps(y, y2);
	y = _mm512_castsi512_ps(_mm512_xor_epi32(_mm512_castps_si512(y), sign_bit));

	return y;
} // sin_ps()