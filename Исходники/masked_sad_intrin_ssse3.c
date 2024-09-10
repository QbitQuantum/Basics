static INLINE unsigned int highbd_masked_sad_ssse3(
    const uint8_t *src8, int src_stride, const uint8_t *a8, int a_stride,
    const uint8_t *b8, int b_stride, const uint8_t *m_ptr, int m_stride,
    int width, int height) {
  const uint16_t *src_ptr = CONVERT_TO_SHORTPTR(src8);
  const uint16_t *a_ptr = CONVERT_TO_SHORTPTR(a8);
  const uint16_t *b_ptr = CONVERT_TO_SHORTPTR(b8);
  int x, y;
  __m128i res = _mm_setzero_si128();
  const __m128i mask_max = _mm_set1_epi16((1 << AOM_BLEND_A64_ROUND_BITS));
  const __m128i round_const =
      _mm_set1_epi32((1 << AOM_BLEND_A64_ROUND_BITS) >> 1);
  const __m128i one = _mm_set1_epi16(1);

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x += 8) {
      const __m128i src = _mm_loadu_si128((const __m128i *)&src_ptr[x]);
      const __m128i a = _mm_loadu_si128((const __m128i *)&a_ptr[x]);
      const __m128i b = _mm_loadu_si128((const __m128i *)&b_ptr[x]);
      // Zero-extend mask to 16 bits
      const __m128i m = _mm_unpacklo_epi8(
          _mm_loadl_epi64((const __m128i *)&m_ptr[x]), _mm_setzero_si128());
      const __m128i m_inv = _mm_sub_epi16(mask_max, m);

      const __m128i data_l = _mm_unpacklo_epi16(a, b);
      const __m128i mask_l = _mm_unpacklo_epi16(m, m_inv);
      __m128i pred_l = _mm_madd_epi16(data_l, mask_l);
      pred_l = _mm_srai_epi32(_mm_add_epi32(pred_l, round_const),
                              AOM_BLEND_A64_ROUND_BITS);

      const __m128i data_r = _mm_unpackhi_epi16(a, b);
      const __m128i mask_r = _mm_unpackhi_epi16(m, m_inv);
      __m128i pred_r = _mm_madd_epi16(data_r, mask_r);
      pred_r = _mm_srai_epi32(_mm_add_epi32(pred_r, round_const),
                              AOM_BLEND_A64_ROUND_BITS);

      // Note: the maximum value in pred_l/r is (2^bd)-1 < 2^15,
      // so it is safe to do signed saturation here.
      const __m128i pred = _mm_packs_epi32(pred_l, pred_r);
      // There is no 16-bit SAD instruction, so we have to synthesize
      // an 8-element SAD. We do this by storing 4 32-bit partial SADs,
      // and accumulating them at the end
      const __m128i diff = _mm_abs_epi16(_mm_sub_epi16(pred, src));
      res = _mm_add_epi32(res, _mm_madd_epi16(diff, one));
    }

    src_ptr += src_stride;
    a_ptr += a_stride;
    b_ptr += b_stride;
    m_ptr += m_stride;
  }
  // At this point, we have four 32-bit partial SADs stored in 'res'.
  res = _mm_hadd_epi32(res, res);
  res = _mm_hadd_epi32(res, res);
  int sad = _mm_cvtsi128_si32(res);
  return (sad + 31) >> 6;
}