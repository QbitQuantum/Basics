/* since sin_ps and cos_ps are almost identical, sincos_ps could replace both of them..
it is almost as fast, and gives you a free cosine with your sine */
void sincos_ps(v4sfu *xptr, v4sfu *sptr, v4sfu *cptr) {
   __m128 x=*((__m128 *)xptr), *s=(__m128 *)sptr, *c=(__m128 *)cptr, xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
#ifdef USE_SSE2
   __m128i emm0, emm2, emm4;
#else
   __m64 mm0, mm1, mm2, mm3, mm4, mm5;
#endif
   sign_bit_sin = x;
   /* take the absolute value */
   x = _mm_and_ps(x, *(__m128*)_ps_inv_sign_mask);
   /* extract the sign bit (upper one) */
   sign_bit_sin = _mm_and_ps(sign_bit_sin, *(__m128*)_ps_sign_mask);

   /* scale by 4/Pi */
   y = _mm_mul_ps(x, *(__m128*)_ps_cephes_FOPI);

#ifdef USE_SSE2
   /* store the integer part of y in emm2 */
   emm2 = _mm_cvttps_epi32(y);

   /* j=(j+1) & (~1) (see the cephes sources) */
   emm2 = _mm_add_epi32(emm2, *(__m128i*)_pi32_1);
   emm2 = _mm_and_si128(emm2, *(__m128i*)_pi32_inv1);
   y = _mm_cvtepi32_ps(emm2);

   emm4 = emm2;

   /* get the swap sign flag for the sine */
   emm0 = _mm_and_si128(emm2, *(__m128i*)_pi32_4);
   emm0 = _mm_slli_epi32(emm0, 29);
   __m128 swap_sign_bit_sin = _mm_castsi128_ps(emm0);

   /* get the polynom selection mask for the sine*/
   emm2 = _mm_and_si128(emm2, *(__m128i*)_pi32_2);
   emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
   __m128 poly_mask = _mm_castsi128_ps(emm2);
#else
   /* store the integer part of y in mm2:mm3 */
   xmm3 = _mm_movehl_ps(xmm3, y);
   mm2 = _mm_cvttps_pi32(y);
   mm3 = _mm_cvttps_pi32(xmm3);

   /* j=(j+1) & (~1) (see the cephes sources) */
   mm2 = _mm_add_pi32(mm2, *(__m64*)_pi32_1);
   mm3 = _mm_add_pi32(mm3, *(__m64*)_pi32_1);
   mm2 = _mm_and_si64(mm2, *(__m64*)_pi32_inv1);
   mm3 = _mm_and_si64(mm3, *(__m64*)_pi32_inv1);

   y = _mm_cvtpi32x2_ps(mm2, mm3);

   mm4 = mm2;
   mm5 = mm3;

   /* get the swap sign flag for the sine */
   mm0 = _mm_and_si64(mm2, *(__m64*)_pi32_4);
   mm1 = _mm_and_si64(mm3, *(__m64*)_pi32_4);
   mm0 = _mm_slli_pi32(mm0, 29);
   mm1 = _mm_slli_pi32(mm1, 29);
   __m128 swap_sign_bit_sin;
   COPY_MM_TO_XMM(mm0, mm1, swap_sign_bit_sin);

   /* get the polynom selection mask for the sine */

   mm2 = _mm_and_si64(mm2, *(__m64*)_pi32_2);
   mm3 = _mm_and_si64(mm3, *(__m64*)_pi32_2);
   mm2 = _mm_cmpeq_pi32(mm2, _mm_setzero_si64());
   mm3 = _mm_cmpeq_pi32(mm3, _mm_setzero_si64());
   __m128 poly_mask;
   COPY_MM_TO_XMM(mm2, mm3, poly_mask);
#endif

   /* The magic pass: "******" 
   x = ((x - y * DP1) - y * DP2) - y * DP3; */
   xmm1 = *(__m128*)_ps_minus_cephes_DP1;
   xmm2 = *(__m128*)_ps_minus_cephes_DP2;
   xmm3 = *(__m128*)_ps_minus_cephes_DP3;
   xmm1 = _mm_mul_ps(y, xmm1);
   xmm2 = _mm_mul_ps(y, xmm2);
   xmm3 = _mm_mul_ps(y, xmm3);
   x = _mm_add_ps(x, xmm1);
   x = _mm_add_ps(x, xmm2);
   x = _mm_add_ps(x, xmm3);

#ifdef USE_SSE2
   emm4 = _mm_sub_epi32(emm4, *(__m128i*)_pi32_2);
   emm4 = _mm_andnot_si128(emm4, *(__m128i*)_pi32_4);
   emm4 = _mm_slli_epi32(emm4, 29);
   __m128 sign_bit_cos = _mm_castsi128_ps(emm4);
#else
   /* get the sign flag for the cosine */
   mm4 = _mm_sub_pi32(mm4, *(__m64*)_pi32_2);
   mm5 = _mm_sub_pi32(mm5, *(__m64*)_pi32_2);
   mm4 = _mm_andnot_si64(mm4, *(__m64*)_pi32_4);
   mm5 = _mm_andnot_si64(mm5, *(__m64*)_pi32_4);
   mm4 = _mm_slli_pi32(mm4, 29);
   mm5 = _mm_slli_pi32(mm5, 29);
   __m128 sign_bit_cos;
   COPY_MM_TO_XMM(mm4, mm5, sign_bit_cos);
   _mm_empty(); /* good-bye mmx */
#endif

   sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);


   /* Evaluate the first polynom  (0 <= x <= Pi/4) */
   __m128 z = _mm_mul_ps(x,x);
   y = *(__m128*)_ps_coscof_p0;

   y = _mm_mul_ps(y, z);
   y = _mm_add_ps(y, *(__m128*)_ps_coscof_p1);
   y = _mm_mul_ps(y, z);
   y = _mm_add_ps(y, *(__m128*)_ps_coscof_p2);
   y = _mm_mul_ps(y, z);
   y = _mm_mul_ps(y, z);
   __m128 tmp = _mm_mul_ps(z, *(__m128*)_ps_0p5);
   y = _mm_sub_ps(y, tmp);
   y = _mm_add_ps(y, *(__m128*)_ps_1);

   /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

   __m128 y2 = *(__m128*)_ps_sincof_p0;
   y2 = _mm_mul_ps(y2, z);
   y2 = _mm_add_ps(y2, *(__m128*)_ps_sincof_p1);
   y2 = _mm_mul_ps(y2, z);
   y2 = _mm_add_ps(y2, *(__m128*)_ps_sincof_p2);
   y2 = _mm_mul_ps(y2, z);
   y2 = _mm_mul_ps(y2, x);
   y2 = _mm_add_ps(y2, x);

   /* select the correct result from the two polynoms */  
   xmm3 = poly_mask;
   __m128 ysin2 = _mm_and_ps(xmm3, y2);
   __m128 ysin1 = _mm_andnot_ps(xmm3, y);
   y2 = _mm_sub_ps(y2,ysin2);
   y = _mm_sub_ps(y, ysin1);

   xmm1 = _mm_add_ps(ysin1,ysin2);
   xmm2 = _mm_add_ps(y,y2);

   /* update the sign */
   *s = _mm_xor_ps(xmm1, sign_bit_sin);
   *c = _mm_xor_ps(xmm2, sign_bit_cos);
}