/* AVX implementation for Minimum Mean Squared Error (MMSE) solver */
inline void srslte_mat_2x2_mmse_avx(__m256 y0, __m256 y1, __m256 h00, __m256 h01, __m256 h10, __m256 h11,
                                        __m256 *x0, __m256 *x1, float noise_estimate, float norm) {
  __m256 _noise_estimate = _mm256_set_ps(0.0f, noise_estimate, 0.0f, noise_estimate,
                                         0.0f, noise_estimate, 0.0f, noise_estimate);
  __m256 _norm = _mm256_set1_ps(norm);

  /* Create conjugated matrix */
  __m256 _h00 = _MM256_CONJ_PS(h00);
  __m256 _h01 = _MM256_CONJ_PS(h01);
  __m256 _h10 = _MM256_CONJ_PS(h10);
  __m256 _h11 = _MM256_CONJ_PS(h11);

  /* 1. A = H' x H + No*/
#ifdef LV_HAVE_FMA
  __m256 a00 = _MM256_SQMOD_ADD_PS(h00, h10, _noise_estimate);
  __m256 a01 = _MM256_PROD_ADD_PS(_h00, h01, _MM256_PROD_PS(_h10, h11));
  __m256 a10 = _MM256_PROD_ADD_PS(_h01, h00, _MM256_PROD_PS(_h11, h10));
  __m256 a11 = _MM256_SQMOD_ADD_PS(h01, h11, _noise_estimate);
#else
  __m256 a00 = _mm256_add_ps(_MM256_SQMOD_PS(h00, h10), _noise_estimate);
  __m256 a01 = _mm256_add_ps(_MM256_PROD_PS(_h00, h01), _MM256_PROD_PS(_h10, h11));
  __m256 a10 = _mm256_add_ps(_MM256_PROD_PS(_h01, h00), _MM256_PROD_PS(_h11, h10));
  __m256 a11 = _mm256_add_ps(_MM256_SQMOD_PS(h01, h11), _noise_estimate);
#endif /* LV_HAVE_FMA */

  /* 2. B = inv(H' x H + No) = inv(A) */
  __m256 b00 = a11;
  __m256 b01 = _mm256_xor_ps(a01, _mm256_set1_ps(-0.0f));
  __m256 b10 = _mm256_xor_ps(a10, _mm256_set1_ps(-0.0f));
  __m256 b11 = a00;
  _norm = _mm256_mul_ps(_norm, srslte_mat_cf_recip_avx(srslte_mat_2x2_det_avx(a00, a01, a10, a11)));


  /* 3. W = inv(H' x H + No) x H' = B x H' */
#ifdef LV_HAVE_FMA
  __m256 w00 = _MM256_PROD_ADD_PS(b00, _h00, _MM256_PROD_PS(b01, _h01));
  __m256 w01 = _MM256_PROD_ADD_PS(b00, _h10, _MM256_PROD_PS(b01, _h11));
  __m256 w10 = _MM256_PROD_ADD_PS(b10, _h00, _MM256_PROD_PS(b11, _h01));
  __m256 w11 = _MM256_PROD_ADD_PS(b10, _h10, _MM256_PROD_PS(b11, _h11));
#else
  __m256 w00 = _mm256_add_ps(_MM256_PROD_PS(b00, _h00), _MM256_PROD_PS(b01, _h01));
  __m256 w01 = _mm256_add_ps(_MM256_PROD_PS(b00, _h10), _MM256_PROD_PS(b01, _h11));
  __m256 w10 = _mm256_add_ps(_MM256_PROD_PS(b10, _h00), _MM256_PROD_PS(b11, _h01));
  __m256 w11 = _mm256_add_ps(_MM256_PROD_PS(b10, _h10), _MM256_PROD_PS(b11, _h11));
#endif /* LV_HAVE_FMA */

  /* 4. X = W x Y */
#ifdef LV_HAVE_FMA
  *x0 = _MM256_PROD_PS(_MM256_PROD_ADD_PS(y0, w00, _MM256_PROD_PS(y1, w01)), _norm);
  *x1 = _MM256_PROD_PS(_MM256_PROD_ADD_PS(y0, w10, _MM256_PROD_PS(y1, w11)), _norm);
#else
  *x0 = _MM256_PROD_PS(_mm256_add_ps(_MM256_PROD_PS(y0, w00), _MM256_PROD_PS(y1, w01)), _norm);
  *x1 = _MM256_PROD_PS(_mm256_add_ps(_MM256_PROD_PS(y0, w10), _MM256_PROD_PS(y1, w11)), _norm);
#endif /* LV_HAVE_FMA */
}