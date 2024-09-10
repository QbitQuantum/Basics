void vp9_add_constant_residual_8x8_sse2(const int16_t diff, uint8_t *dest,
                                        int stride) {
  uint8_t abs_diff;
  __m128i d;

  // Prediction data.
  __m128i p0 = _mm_loadl_epi64((const __m128i *)(dest + 0 * stride));
  __m128i p1 = _mm_loadl_epi64((const __m128i *)(dest + 1 * stride));
  __m128i p2 = _mm_loadl_epi64((const __m128i *)(dest + 2 * stride));
  __m128i p3 = _mm_loadl_epi64((const __m128i *)(dest + 3 * stride));
  __m128i p4 = _mm_loadl_epi64((const __m128i *)(dest + 4 * stride));
  __m128i p5 = _mm_loadl_epi64((const __m128i *)(dest + 5 * stride));
  __m128i p6 = _mm_loadl_epi64((const __m128i *)(dest + 6 * stride));
  __m128i p7 = _mm_loadl_epi64((const __m128i *)(dest + 7 * stride));

  p0 = _mm_unpacklo_epi64(p0, p1);
  p2 = _mm_unpacklo_epi64(p2, p3);
  p4 = _mm_unpacklo_epi64(p4, p5);
  p6 = _mm_unpacklo_epi64(p6, p7);

  // Clip diff value to [0, 255] range. Then, do addition or subtraction
  // according to its sign.
  if (diff >= 0) {
    abs_diff = (diff > 255) ? 255 : diff;
    d = _mm_shuffle_epi32(_mm_cvtsi32_si128((int)(abs_diff * 0x01010101u)), 0);

    p0 = _mm_adds_epu8(p0, d);
    p2 = _mm_adds_epu8(p2, d);
    p4 = _mm_adds_epu8(p4, d);
    p6 = _mm_adds_epu8(p6, d);
  } else {
    abs_diff = (diff < -255) ? 255 : -diff;
    d = _mm_shuffle_epi32(_mm_cvtsi32_si128((int)(abs_diff * 0x01010101u)), 0);

    p0 = _mm_subs_epu8(p0, d);
    p2 = _mm_subs_epu8(p2, d);
    p4 = _mm_subs_epu8(p4, d);
    p6 = _mm_subs_epu8(p6, d);
  }

  _mm_storel_epi64((__m128i *)(dest + 0 * stride), p0);
  p0 = _mm_srli_si128(p0, 8);
  _mm_storel_epi64((__m128i *)(dest + 1 * stride), p0);

  _mm_storel_epi64((__m128i *)(dest + 2 * stride), p2);
  p2 = _mm_srli_si128(p2, 8);
  _mm_storel_epi64((__m128i *)(dest + 3 * stride), p2);

  _mm_storel_epi64((__m128i *)(dest + 4 * stride), p4);
  p4 = _mm_srli_si128(p4, 8);
  _mm_storel_epi64((__m128i *)(dest + 5 * stride), p4);

  _mm_storel_epi64((__m128i *)(dest + 6 * stride), p6);
  p6 = _mm_srli_si128(p6, 8);
  _mm_storel_epi64((__m128i *)(dest + 7 * stride), p6);
}