void aom_highbd_quantize_b_sse2(const tran_low_t *coeff_ptr, intptr_t count,
                                int skip_block, const int16_t *zbin_ptr,
                                const int16_t *round_ptr,
                                const int16_t *quant_ptr,
                                const int16_t *quant_shift_ptr,
                                tran_low_t *qcoeff_ptr, tran_low_t *dqcoeff_ptr,
                                const int16_t *dequant_ptr, uint16_t *eob_ptr,
                                const int16_t *scan, const int16_t *iscan) {
  int i, j, non_zero_regs = (int)count / 4, eob_i = -1;
  __m128i zbins[2];
  __m128i nzbins[2];

  zbins[0] = _mm_set_epi32((int)zbin_ptr[1], (int)zbin_ptr[1], (int)zbin_ptr[1],
                           (int)zbin_ptr[0]);
  zbins[1] = _mm_set1_epi32((int)zbin_ptr[1]);

  nzbins[0] = _mm_setzero_si128();
  nzbins[1] = _mm_setzero_si128();
  nzbins[0] = _mm_sub_epi32(nzbins[0], zbins[0]);
  nzbins[1] = _mm_sub_epi32(nzbins[1], zbins[1]);

  (void)scan;

  memset(qcoeff_ptr, 0, count * sizeof(*qcoeff_ptr));
  memset(dqcoeff_ptr, 0, count * sizeof(*dqcoeff_ptr));

  if (!skip_block) {
    // Pre-scan pass
    for (i = ((int)count / 4) - 1; i >= 0; i--) {
      __m128i coeffs, cmp1, cmp2;
      int test;
      coeffs = _mm_load_si128((const __m128i *)(coeff_ptr + i * 4));
      cmp1 = _mm_cmplt_epi32(coeffs, zbins[i != 0]);
      cmp2 = _mm_cmpgt_epi32(coeffs, nzbins[i != 0]);
      cmp1 = _mm_and_si128(cmp1, cmp2);
      test = _mm_movemask_epi8(cmp1);
      if (test == 0xffff)
        non_zero_regs--;
      else
        break;
    }

    // Quantization pass:
    for (i = 0; i < non_zero_regs; i++) {
      __m128i coeffs, coeffs_sign, tmp1, tmp2;
      int test;
      int abs_coeff[4];
      int coeff_sign[4];

      coeffs = _mm_load_si128((const __m128i *)(coeff_ptr + i * 4));
      coeffs_sign = _mm_srai_epi32(coeffs, 31);
      coeffs = _mm_sub_epi32(_mm_xor_si128(coeffs, coeffs_sign), coeffs_sign);
      tmp1 = _mm_cmpgt_epi32(coeffs, zbins[i != 0]);
      tmp2 = _mm_cmpeq_epi32(coeffs, zbins[i != 0]);
      tmp1 = _mm_or_si128(tmp1, tmp2);
      test = _mm_movemask_epi8(tmp1);
      _mm_storeu_si128((__m128i *)abs_coeff, coeffs);
      _mm_storeu_si128((__m128i *)coeff_sign, coeffs_sign);

      for (j = 0; j < 4; j++) {
        if (test & (1 << (4 * j))) {
          int k = 4 * i + j;
          const int64_t tmp3 = abs_coeff[j] + round_ptr[k != 0];
          const int64_t tmp4 = ((tmp3 * quant_ptr[k != 0]) >> 16) + tmp3;
          const uint32_t abs_qcoeff =
              (uint32_t)((tmp4 * quant_shift_ptr[k != 0]) >> 16);
          qcoeff_ptr[k] = (int)(abs_qcoeff ^ coeff_sign[j]) - coeff_sign[j];
          dqcoeff_ptr[k] = qcoeff_ptr[k] * dequant_ptr[k != 0];
          if (abs_qcoeff) eob_i = iscan[k] > eob_i ? iscan[k] : eob_i;
        }
      }
    }
  }