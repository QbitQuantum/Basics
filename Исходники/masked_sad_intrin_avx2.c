static INLINE unsigned int masked_sad32xh_avx2(
    const uint8_t *src_ptr, int src_stride, const uint8_t *a_ptr, int a_stride,
    const uint8_t *b_ptr, int b_stride, const uint8_t *m_ptr, int m_stride,
    int width, int height) {
  int x, y;
  __m256i res = _mm256_setzero_si256();
  const __m256i mask_max = _mm256_set1_epi8((1 << AOM_BLEND_A64_ROUND_BITS));
  const __m256i round_scale =
      _mm256_set1_epi16(1 << (15 - AOM_BLEND_A64_ROUND_BITS));
  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x += 32) {
      const __m256i src = _mm256_lddqu_si256((const __m256i *)&src_ptr[x]);
      const __m256i a = _mm256_lddqu_si256((const __m256i *)&a_ptr[x]);
      const __m256i b = _mm256_lddqu_si256((const __m256i *)&b_ptr[x]);
      const __m256i m = _mm256_lddqu_si256((const __m256i *)&m_ptr[x]);
      const __m256i m_inv = _mm256_sub_epi8(mask_max, m);

      // Calculate 16 predicted pixels.
      // Note that the maximum value of any entry of 'pred_l' or 'pred_r'
      // is 64 * 255, so we have plenty of space to add rounding constants.
      const __m256i data_l = _mm256_unpacklo_epi8(a, b);
      const __m256i mask_l = _mm256_unpacklo_epi8(m, m_inv);
      __m256i pred_l = _mm256_maddubs_epi16(data_l, mask_l);
      pred_l = _mm256_mulhrs_epi16(pred_l, round_scale);

      const __m256i data_r = _mm256_unpackhi_epi8(a, b);
      const __m256i mask_r = _mm256_unpackhi_epi8(m, m_inv);
      __m256i pred_r = _mm256_maddubs_epi16(data_r, mask_r);
      pred_r = _mm256_mulhrs_epi16(pred_r, round_scale);

      const __m256i pred = _mm256_packus_epi16(pred_l, pred_r);
      res = _mm256_add_epi32(res, _mm256_sad_epu8(pred, src));
    }

    src_ptr += src_stride;
    a_ptr += a_stride;
    b_ptr += b_stride;
    m_ptr += m_stride;
  }
  // At this point, we have two 32-bit partial SADs in lanes 0 and 2 of 'res'.
  res = _mm256_shuffle_epi32(res, 0xd8);
  res = _mm256_permute4x64_epi64(res, 0xd8);
  res = _mm256_hadd_epi32(res, res);
  res = _mm256_hadd_epi32(res, res);
  int32_t sad = _mm256_extract_epi32(res, 0);
  return (sad + 31) >> 6;
}