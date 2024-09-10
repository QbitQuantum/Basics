uint8_t
get_xE_avx(const ESL_DSQ *dsq, int L, const P7_OPROFILE *om)
{
#ifdef HAVE_AVX2
  __m256i xEv_AVX;		           /* E state: keeps max for Mk->E as we go                     */
  __m256i beginv_AVX;                  /* begin scores                                              */
  uint8_t retval_AVX;
  int q_AVX;			   /* counter over vectors 0..nq-1                              */
  int Q_AVX        = P7_NVB_AVX(om->M);   /* segment length: # of vectors                              */

  int bands_AVX;                       /* the number of bands (rounds) to use                       */
  beginv_AVX =  _mm256_set1_epi8(128);
  xEv_AVX    =  beginv_AVX;
  /* function pointers for the various number of vectors to use */
  __m256i (*fs_AVX[MAX_BANDS + 1]) (const ESL_DSQ *, int, const P7_OPROFILE *, int, register __m256i, __m256i)
    = {NULL
       , calc_band_1_AVX,  calc_band_2_AVX,  calc_band_3_AVX,  calc_band_4_AVX,  calc_band_5_AVX,  calc_band_6_AVX
#if MAX_BANDS > 6
       , calc_band_7_AVX,  calc_band_8_AVX,  calc_band_9_AVX,  calc_band_10_AVX, calc_band_11_AVX, calc_band_12_AVX
       , calc_band_13_AVX, calc_band_14_AVX
#endif
#if MAX_BANDS > 14
       , calc_band_15_AVX, calc_band_16_AVX, calc_band_17_AVX, calc_band_18_AVX
#endif
  };

  int last_q;                  /* for saving the last q value to find band width            */
  int i;                           /* counter for bands                                         */

  last_q = 0; // reset in case we also ran SSE code
  /* Use the highest number of bands but no more than MAX_BANDS */
  bands_AVX = (Q_AVX + MAX_BANDS - 1) / MAX_BANDS;
  for (i = 0; i < bands_AVX; i++) {
    q_AVX = (Q_AVX * (i + 1)) / bands_AVX;

    xEv_AVX = fs_AVX[q_AVX-last_q](dsq, L, om, last_q, beginv_AVX, xEv_AVX);

    last_q = q_AVX;
  }

 
  retval_AVX = esl_avx_hmax_epu8(xEv_AVX);

  return retval_AVX;
#endif // HAVE_AVX2
#ifndef HAVE_AVX2
  	return 0;  // Stub so there's something to link if we don't have AVX2 support
#endif
}