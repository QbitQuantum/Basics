inline avx_m256_t newsin_ps(avx_m256_t x) {
	avx_m256_t sign_bit = _mm256_and_ps(x, _ps_sign_mask);
	x = _mm256_and_ps(x, _ps_inv_sign_mask);
	
	avx_m256_t y = _mm256_mul_ps(x, _ps_cephes_FOPI);

	avx_m256i_t emm2 = _mm256_cvttps_epi32(y);
	emm2 = _mm256_add_epi32(emm2, _pi32_1);
	emm2 = _mm256_and_si256(emm2, _pi32_inv1);
	y = _mm256_cvtepi32_ps(emm2);

	avx_m256i_t emm0 = _mm256_and_si256(emm2, _pi32_4);
	emm0 = _mm256_slli_epi32(emm0, 29);

	emm2 = _mm256_and_si256(emm2, _pi32_2);
	emm2 = _mm256_cmpeq_epi32(emm2, _mm256_setzero_si256());
	
	avx_m256_t swap_sign_bit = _mm256_castsi256_ps(emm0);
	avx_m256_t poly_mask = _mm256_castsi256_ps(emm2);
	sign_bit = _mm256_xor_ps(sign_bit, swap_sign_bit);
	
	avx_m256_t temp = _ps_minus_cephes_DP123;
	temp = _mm256_mul_ps(y, temp);
	x = _mm256_add_ps(x, temp);

	avx_m256_t x2 = _mm256_mul_ps(x, x);
	avx_m256_t x3 = _mm256_mul_ps(x2, x);
	avx_m256_t x4 = _mm256_mul_ps(x2, x2);

	y = _ps_coscof_p0;
	avx_m256_t y2 = _ps_sincof_p0;
	y = _mm256_mul_ps(y, x2);
	y2 = _mm256_mul_ps(y2, x2);
	y = _mm256_add_ps(y, _ps_coscof_p1);
	y2 = _mm256_add_ps(y2, _ps_sincof_p1);
	y = _mm256_mul_ps(y, x2);
	y2 = _mm256_mul_ps(y2, x2);
	y = _mm256_add_ps(y, _ps_coscof_p2);
	y2 = _mm256_add_ps(y2, _ps_sincof_p2);
	y = _mm256_mul_ps(y, x4);
	y2 = _mm256_mul_ps(y2, x3);
	temp = _mm256_mul_ps(x2, _ps_0p5);
	temp = _mm256_sub_ps(temp, _ps_1);
	y = _mm256_sub_ps(y, temp);
	y2 = _mm256_add_ps(y2, x);

	y = _mm256_andnot_ps(poly_mask, y);
	y2 = _mm256_and_ps(poly_mask, y2);
	y = _mm256_add_ps(y, y2);

	y = _mm256_xor_ps(y, sign_bit);

	return y;
} // newsin_ps()