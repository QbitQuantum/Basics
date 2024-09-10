__m256 mm256_cos_ps(__m256 x) {
  __m256 xmm1, xmm2 = _mm256_setzero_ps(), xmm3, y;
  __m256i emm0, emm2;
  /* take the absolute value */
  x = _mm256_and_ps(x, *(__m256*)m256_ps_inv_sign_mask);
  
  /* scale by 4/Pi */
  y = _mm256_mul_ps(x, *(__m256*)m256_ps_cephes_FOPI);

  /* store the integer part of y in mm0 */
  emm2 = _mm256_cvttps_epi32(y);
  /* j=(j+1) & (~1) (see the cephes sources) */
  emm2 = _mm256_add_epi32(emm2, *(__m256i*)m256_pi32_1);
  emm2 = _mm256_and_si256(emm2, *(__m256i*)m256_pi32_inv1);
  y = _mm256_cvtepi32_ps(emm2);

  emm2 = _mm256_sub_epi32(emm2, *(__m256i*)m256_pi32_2);
  
  /* get the swap sign flag */
  emm0 = _mm256_andnot_si256(emm2, *(__m256i*)m256_pi32_4);
  emm0 = _mm256_slli_epi32(emm0, 29);
  /* get the polynom selection mask */
  emm2 = _mm256_and_si256(emm2, *(__m256i*)m256_pi32_2);
  emm2 = _mm256_cmpeq_epi32(emm2, _mm256_setzero_si256());
  
  __m256 sign_bit = _mm256_castsi256_ps(emm0);
  __m256 poly_mask = _mm256_castsi256_ps(emm2);

  /* The magic pass: "******" 
     x = ((x - y * DP1) - y * DP2) - y * DP3; */
  xmm1 = *(__m256*)m256_ps_minus_cephes_DP1;
  xmm2 = *(__m256*)m256_ps_minus_cephes_DP2;
  xmm3 = *(__m256*)m256_ps_minus_cephes_DP3;
  xmm1 = _mm256_mul_ps(y, xmm1);
  xmm2 = _mm256_mul_ps(y, xmm2);
  xmm3 = _mm256_mul_ps(y, xmm3);
  x = _mm256_add_ps(x, xmm1);
  x = _mm256_add_ps(x, xmm2);
  x = _mm256_add_ps(x, xmm3);
  
  /* Evaluate the first polynom  (0 <= x <= Pi/4) */
  y = *(__m256*)m256_ps_coscof_p0;
  __m256 z = _mm256_mul_ps(x,x);

  y = _mm256_mul_ps(y, z);
  y = _mm256_add_ps(y, *(__m256*)m256_ps_coscof_p1);
  y = _mm256_mul_ps(y, z);
  y = _mm256_add_ps(y, *(__m256*)m256_ps_coscof_p2);
  y = _mm256_mul_ps(y, z);
  y = _mm256_mul_ps(y, z);
  __m256 tmp = _mm256_mul_ps(z, *(__m256*)m256_ps_0p5);
  y = _mm256_sub_ps(y, tmp);
  y = _mm256_add_ps(y, *(__m256*)m256_ps_1);
  
  /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

  __m256 y2 = *(__m256*)m256_ps_sincof_p0;
  y2 = _mm256_mul_ps(y2, z);
  y2 = _mm256_add_ps(y2, *(__m256*)m256_ps_sincof_p1);
  y2 = _mm256_mul_ps(y2, z);
  y2 = _mm256_add_ps(y2, *(__m256*)m256_ps_sincof_p2);
  y2 = _mm256_mul_ps(y2, z);
  y2 = _mm256_mul_ps(y2, x);
  y2 = _mm256_add_ps(y2, x);

  /* select the correct result from the two polynoms */  
  xmm3 = poly_mask;
  y2 = _mm256_and_ps(xmm3, y2); //, xmm3);
  y = _mm256_andnot_ps(xmm3, y);
  y = _mm256_add_ps(y,y2);
  /* update the sign */
  y = _mm256_xor_ps(y, sign_bit);

  _mm256_zeroupper();
  return y;
}