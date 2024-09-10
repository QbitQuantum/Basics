static INLINE void cfl_predict_hbd_ssse3(const int16_t *pred_buf_q3,
                                         uint16_t *dst, int dst_stride,
                                         int alpha_q3, int bd, int width,
                                         int height) {
  const __m128i alpha_sign = _mm_set1_epi16(alpha_q3);
  const __m128i alpha_q12 = _mm_slli_epi16(_mm_abs_epi16(alpha_sign), 9);
  const __m128i dc_q0 = _mm_set1_epi16(*dst);
  const __m128i max = highbd_max_epi16(bd);
  const __m128i zeros = _mm_setzero_si128();
  __m128i *row = (__m128i *)pred_buf_q3;
  const __m128i *row_end = row + height * CFL_BUF_LINE_I128;
  do {
    __m128i res = predict_unclipped(row, alpha_q12, alpha_sign, dc_q0);
    res = highbd_clamp_epi16(res, zeros, max);
    if (width == 4) {
      _mm_storel_epi64((__m128i *)dst, res);
    } else {
      _mm_storeu_si128((__m128i *)dst, res);
    }
    if (width >= 16) {
      const __m128i res_1 =
          predict_unclipped(row + 1, alpha_q12, alpha_sign, dc_q0);
      _mm_storeu_si128(((__m128i *)dst) + 1,
                       highbd_clamp_epi16(res_1, zeros, max));
    }
    if (width == 32) {
      const __m128i res_2 =
          predict_unclipped(row + 2, alpha_q12, alpha_sign, dc_q0);
      _mm_storeu_si128((__m128i *)(dst + 16),
                       highbd_clamp_epi16(res_2, zeros, max));
      const __m128i res_3 =
          predict_unclipped(row + 3, alpha_q12, alpha_sign, dc_q0);
      _mm_storeu_si128((__m128i *)(dst + 24),
                       highbd_clamp_epi16(res_3, zeros, max));
    }
    dst += dst_stride;
  } while ((row += CFL_BUF_LINE_I128) < row_end);
}