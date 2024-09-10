void decomp_gamma2_plus( spinor_array src, halfspinor_array dst) 
{
  /* Space for upper components */
  __m128 xmm0;
  __m128 xmm1;
  __m128 xmm2;

  /* Space for lower components */
  __m128 xmm3;
  __m128 xmm4;
  __m128 xmm5;

  /* Swap upper and lower components */
  /* Compiler should spill, or use 64 bit extras */
  __m128 xmm6;
  __m128 xmm7;
  __m128 xmm8;

  /* Swap upper and lower components */
  /* Compiler should spill, or use 64 bit extras */
  __m128 xmm9;
  __m128 xmm10;
  __m128 xmm11;


  xmm0 = _mm_load_ps(&src[0][0][0]);
  xmm2 = _mm_load_ps(&src[0][2][0]);
  xmm6 = _mm_load_ps(&src[1][1][0]);
  
  xmm3 = _mm_load_ps(&src[2][0][0]);
  xmm5 = _mm_load_ps(&src[2][2][0]);
  xmm7 = _mm_load_ps(&src[3][1][0]);

  xmm1 = _mm_xor_ps(xmm1,xmm1); // This should zero 
  xmm4 = _mm_xor_ps(xmm4,xmm4);

  xmm1 = _mm_movelh_ps(xmm1,xmm6);
  xmm4 = _mm_movelh_ps(xmm4,xmm7);

  xmm1 = _mm_movehl_ps(xmm1, xmm0);
  xmm4 = _mm_movehl_ps(xmm4, xmm3);


  xmm0 = _mm_shuffle_ps(xmm0, xmm2, 0xe4);
  xmm3 = _mm_shuffle_ps(xmm3, xmm5, 0xe4);

  xmm2 = _mm_shuffle_ps(xmm2, xmm6, 0xe4);
  xmm5 = _mm_shuffle_ps(xmm5, xmm7, 0xe4);

#if 0
  /* Load up the spinors */
  xmm0 = _mm_loadl_pi(xmm0, (__m64 *)&src[0][0][0]);
  xmm1 = _mm_loadl_pi(xmm1, (__m64 *)&src[0][1][0]);
  xmm2 = _mm_loadl_pi(xmm2, (__m64 *)&src[0][2][0]);

  xmm0 = _mm_loadh_pi(xmm0, (__m64 *)&src[1][0][0]);
  xmm1 = _mm_loadh_pi(xmm1, (__m64 *)&src[1][1][0]);
  xmm2 = _mm_loadh_pi(xmm2, (__m64 *)&src[1][2][0]);

  xmm3 = _mm_loadl_pi(xmm3, (__m64 *)&src[2][0][0]);
  xmm4 = _mm_loadl_pi(xmm4, (__m64 *)&src[2][1][0]);
  xmm5 = _mm_loadl_pi(xmm5, (__m64 *)&src[2][2][0]);

  xmm3 = _mm_loadh_pi(xmm3, (__m64 *)&src[3][0][0]);
  xmm4 = _mm_loadh_pi(xmm4, (__m64 *)&src[3][1][0]);
  xmm5 = _mm_loadh_pi(xmm5, (__m64 *)&src[3][2][0]);

#endif
 
  /* Swap the lower components */
  xmm6 = _mm_shuffle_ps(xmm3, xmm3, 0xb1);
  xmm7 = _mm_shuffle_ps(xmm4, xmm4, 0xb1);
  xmm8 = _mm_shuffle_ps(xmm5, xmm5, 0xb1);

  xmm9 = _mm_xor_ps(xmm6, signs14.vector);
  xmm10 = _mm_xor_ps(xmm7, signs14.vector);
  xmm11 = _mm_xor_ps(xmm8, signs14.vector);

  /* Add */
  xmm0 = _mm_add_ps(xmm0, xmm9);
  xmm1 = _mm_add_ps(xmm1, xmm10);
  xmm2 = _mm_add_ps(xmm2, xmm11);

  /* Store */
  _mm_store_ps(&dst[0][0][0],xmm0);
  _mm_store_ps(&dst[1][0][0],xmm1);
  _mm_store_ps(&dst[2][0][0],xmm2);


}