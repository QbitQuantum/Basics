void sincos_ps(__m128 x, __m128 *s, __m128 *c) {
  __m128 xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
  __m128i emm0, emm2, emm4;
  sign_bit_sin = x;
  x = _mm_and_ps(x, *reinterpret_cast<const __m128*>(_pi_inv_sign_mask));
  sign_bit_sin = _mm_and_ps(sign_bit_sin,
                            *reinterpret_cast<const __m128*>(_pi_sign_mask));
  y = _mm_mul_ps(x, *_ps_cephes_FOPI);
  emm2 = _mm_cvttps_epi32(y);
  emm2 = _mm_add_epi32(emm2, *_pi_1);
  emm2 = _mm_and_si128(emm2, *_pi_inv1);
  y = _mm_cvtepi32_ps(emm2);
  emm4 = emm2;
  emm0 = _mm_and_si128(emm2, *_pi_4);
  emm0 = _mm_slli_epi32(emm0, 29);
  __m128 swap_sign_bit_sin = _mm_castsi128_ps(emm0);
  emm2 = _mm_and_si128(emm2, *_pi_2);
  emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
  __m128 poly_mask = _mm_castsi128_ps(emm2);
  xmm1 = *_ps_minus_cephes_DP1;
  xmm2 = *_ps_minus_cephes_DP2;
  xmm3 = *_ps_minus_cephes_DP3;
  xmm1 = _mm_mul_ps(y, xmm1);
  xmm2 = _mm_mul_ps(y, xmm2);
  xmm3 = _mm_mul_ps(y, xmm3);
  x = _mm_add_ps(x, xmm1);
  x = _mm_add_ps(x, xmm2);
  x = _mm_add_ps(x, xmm3);
  emm4 = _mm_sub_epi32(emm4, *_pi_2);
  emm4 = _mm_andnot_si128(emm4, *_pi_4);
  emm4 = _mm_slli_epi32(emm4, 29);
  __m128 sign_bit_cos = _mm_castsi128_ps(emm4);
  sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);
  __m128 z = _mm_mul_ps(x, x);
  y = *_ps_coscof_p0;
  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *_ps_coscof_p1);
  y = _mm_mul_ps(y, z);
  y = _mm_add_ps(y, *_ps_coscof_p2);
  y = _mm_mul_ps(y, z);
  y = _mm_mul_ps(y, z);
  __m128 tmp = _mm_mul_ps(z, *_ps_0p5);
  y = _mm_sub_ps(y, tmp);
  y = _mm_add_ps(y, *_ps_1);
  __m128 y2 = *_ps_sincof_p0;
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *_ps_sincof_p1);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_add_ps(y2, *_ps_sincof_p2);
  y2 = _mm_mul_ps(y2, z);
  y2 = _mm_mul_ps(y2, x);
  y2 = _mm_add_ps(y2, x);
  xmm3 = poly_mask;
  __m128 ysin2 = _mm_and_ps(xmm3, y2);
  __m128 ysin1 = _mm_andnot_ps(xmm3, y);
  y2 = _mm_sub_ps(y2, ysin2);
  y = _mm_sub_ps(y, ysin1);
  xmm1 = _mm_add_ps(ysin1, ysin2);
  xmm2 = _mm_add_ps(y, y2);
  *s = _mm_xor_ps(xmm1, sign_bit_sin);
  *c = _mm_xor_ps(xmm2, sign_bit_cos);
}