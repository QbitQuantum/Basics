static INLINE unsigned int hbd_obmc_sad_w8n(const uint8_t *pre8,
                                            const int pre_stride,
                                            const int32_t *wsrc,
                                            const int32_t *mask,
                                            const int width, const int height) {
  const uint16_t *pre = CONVERT_TO_SHORTPTR(pre8);
  const int pre_step = pre_stride - width;
  int n = 0;
  __m128i v_sad_d = _mm_setzero_si128();

  assert(width >= 8);
  assert(IS_POWER_OF_TWO(width));

  do {
    const __m128i v_p1_w = xx_loadl_64(pre + n + 4);
    const __m128i v_m1_d = xx_load_128(mask + n + 4);
    const __m128i v_w1_d = xx_load_128(wsrc + n + 4);
    const __m128i v_p0_w = xx_loadl_64(pre + n);
    const __m128i v_m0_d = xx_load_128(mask + n);
    const __m128i v_w0_d = xx_load_128(wsrc + n);

    const __m128i v_p0_d = _mm_cvtepu16_epi32(v_p0_w);
    const __m128i v_p1_d = _mm_cvtepu16_epi32(v_p1_w);

    // Values in both pre and mask fit in 15 bits, and are packed at 32 bit
    // boundaries. We use pmaddwd, as it has lower latency on Haswell
    // than pmulld but produces the same result with these inputs.
    const __m128i v_pm0_d = _mm_madd_epi16(v_p0_d, v_m0_d);
    const __m128i v_pm1_d = _mm_madd_epi16(v_p1_d, v_m1_d);

    const __m128i v_diff0_d = _mm_sub_epi32(v_w0_d, v_pm0_d);
    const __m128i v_diff1_d = _mm_sub_epi32(v_w1_d, v_pm1_d);
    const __m128i v_absdiff0_d = _mm_abs_epi32(v_diff0_d);
    const __m128i v_absdiff1_d = _mm_abs_epi32(v_diff1_d);

    // Rounded absolute difference
    const __m128i v_rad0_d = xx_roundn_epu32(v_absdiff0_d, 12);
    const __m128i v_rad1_d = xx_roundn_epu32(v_absdiff1_d, 12);

    v_sad_d = _mm_add_epi32(v_sad_d, v_rad0_d);
    v_sad_d = _mm_add_epi32(v_sad_d, v_rad1_d);

    n += 8;

    if (n % width == 0) pre += pre_step;
  } while (n < width * height);

  return xx_hsum_epi32_si32(v_sad_d);
}