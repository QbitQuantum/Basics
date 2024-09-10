/* since sin_ps and cos_ps are almost identical, sincos_ps could replace both of them..
   it is almost as fast, and gives you a free cosine with your sine */
void sincos_ps(__m128 x, __m128* s, __m128* c) {
    typedef __m128 v4sf;
    typedef __m128i v4si;

    v4sf xmm1, xmm2, xmm3 = _mm_setzero_ps(), sign_bit_sin, y;
    v4si emm0, emm2, emm4;
    sign_bit_sin = x;
    /* take the absolute value */
    x = _mm_and_ps(x, constants::inv_sign_mask.ps);
    /* extract the sign bit (upper one) */
    sign_bit_sin = _mm_and_ps(sign_bit_sin, constants::sign_mask.ps);

    /* scale by 4/Pi */
    y = _mm_mul_ps(x, constants::cephes_FOPI.ps);

    /* store the integer part of y in emm2 */
    emm2 = _mm_cvttps_epi32(y);

    /* j=(j+1) & (~1) (see the cephes sources) */
    emm2 = _mm_add_epi32(emm2, constants::pi32_1.pi);
    emm2 = _mm_and_si128(emm2, constants::pi32_inv1.pi);
    y = _mm_cvtepi32_ps(emm2);

    emm4 = emm2;

    /* get the swap sign flag for the sine */
    emm0 = _mm_and_si128(emm2, constants::pi32_4.pi);
    emm0 = _mm_slli_epi32(emm0, 29);
    v4sf swap_sign_bit_sin = _mm_castsi128_ps(emm0);

    /* get the polynom selection mask for the sine*/
    emm2 = _mm_and_si128(emm2, constants::pi32_2.pi);
    emm2 = _mm_cmpeq_epi32(emm2, _mm_setzero_si128());
    v4sf poly_mask = _mm_castsi128_ps(emm2);

    /* The magic pass: "******"
    x = ((x - y * DP1) - y * DP2) - y * DP3; */
    xmm1 = constants::minus_cephes_DP1.ps;
    xmm2 = constants::minus_cephes_DP2.ps;
    xmm3 = constants::minus_cephes_DP3.ps;
    xmm1 = _mm_mul_ps(y, xmm1);
    xmm2 = _mm_mul_ps(y, xmm2);
    xmm3 = _mm_mul_ps(y, xmm3);
    x = _mm_add_ps(x, xmm1);
    x = _mm_add_ps(x, xmm2);
    x = _mm_add_ps(x, xmm3);

    emm4 = _mm_sub_epi32(emm4, constants::pi32_2.pi);
    emm4 = _mm_andnot_si128(emm4, constants::pi32_4.pi);
    emm4 = _mm_slli_epi32(emm4, 29);
    v4sf sign_bit_cos = _mm_castsi128_ps(emm4);

    sign_bit_sin = _mm_xor_ps(sign_bit_sin, swap_sign_bit_sin);


    /* Evaluate the first polynom  (0 <= x <= Pi/4) */
    v4sf z = _mm_mul_ps(x,x);
    y = constants::coscof_p0.ps;

    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, constants::coscof_p1.ps);
    y = _mm_mul_ps(y, z);
    y = _mm_add_ps(y, constants::coscof_p2.ps);
    y = _mm_mul_ps(y, z);
    y = _mm_mul_ps(y, z);
    v4sf tmp = _mm_mul_ps(z, constants::ps_0p5.ps);
    y = _mm_sub_ps(y, tmp);
    y = _mm_add_ps(y, constants::ps_1.ps);

    /* Evaluate the second polynom  (Pi/4 <= x <= 0) */

    v4sf y2 = constants::sincof_p0.ps;
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, constants::sincof_p1.ps);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_add_ps(y2, constants::sincof_p2.ps);
    y2 = _mm_mul_ps(y2, z);
    y2 = _mm_mul_ps(y2, x);
    y2 = _mm_add_ps(y2, x);

    /* select the correct result from the two polynoms */
    xmm3 = poly_mask;
    v4sf ysin2 = _mm_and_ps(xmm3, y2);
    v4sf ysin1 = _mm_andnot_ps(xmm3, y);
    y2 = _mm_sub_ps(y2,ysin2);
    y = _mm_sub_ps(y, ysin1);

    xmm1 = _mm_add_ps(ysin1,ysin2);
    xmm2 = _mm_add_ps(y,y2);

    /* update the sign */
    *s = _mm_xor_ps(xmm1, sign_bit_sin);
    *c = _mm_xor_ps(xmm2, sign_bit_cos);
}