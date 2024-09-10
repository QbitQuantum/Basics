void aom_highbd_upsampled_pred_sse2(uint16_t *pred, int width, int height,
                                    const uint8_t *ref8, const int ref_stride) {
  const int stride = ref_stride << 3;
  uint16_t *ref = CONVERT_TO_SHORTPTR(ref8);
  int i, j;

  if (width >= 8) {
    // read 8 points at one time
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j += 8) {
        __m128i s0 = _mm_cvtsi32_si128(*(const uint32_t *)ref);
        __m128i s1 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 8));
        __m128i s2 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 16));
        __m128i s3 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 24));
        __m128i s4 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 32));
        __m128i s5 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 40));
        __m128i s6 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 48));
        __m128i s7 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 56));
        __m128i t0, t1, t2, t3;

        t0 = _mm_unpacklo_epi16(s0, s1);
        t1 = _mm_unpacklo_epi16(s2, s3);
        t2 = _mm_unpacklo_epi16(s4, s5);
        t3 = _mm_unpacklo_epi16(s6, s7);
        t0 = _mm_unpacklo_epi32(t0, t1);
        t2 = _mm_unpacklo_epi32(t2, t3);
        t0 = _mm_unpacklo_epi64(t0, t2);

        _mm_storeu_si128((__m128i *)(pred), t0);
        pred += 8;
        ref += 64;  // 8 * 8;
      }
      ref += stride - (width << 3);
    }
  } else {
    // read 4 points at one time
    for (i = 0; i < height; i++) {
      for (j = 0; j < width; j += 4) {
        __m128i s0 = _mm_cvtsi32_si128(*(const uint32_t *)ref);
        __m128i s1 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 8));
        __m128i s2 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 16));
        __m128i s3 = _mm_cvtsi32_si128(*(const uint32_t *)(ref + 24));
        __m128i t0, t1;

        t0 = _mm_unpacklo_epi16(s0, s1);
        t1 = _mm_unpacklo_epi16(s2, s3);
        t0 = _mm_unpacklo_epi32(t0, t1);

        _mm_storel_epi64((__m128i *)(pred), t0);
        pred += 4;
        ref += 4 * 8;
      }
      ref += stride - (width << 3);
    }
  }
}