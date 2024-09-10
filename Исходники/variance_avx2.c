void aom_highbd_comp_mask_pred_avx2(uint8_t *comp_pred8, const uint8_t *pred8,
                                    int width, int height, const uint8_t *ref8,
                                    int ref_stride, const uint8_t *mask,
                                    int mask_stride, int invert_mask) {
  int i = 0;
  uint16_t *pred = CONVERT_TO_SHORTPTR(pred8);
  uint16_t *ref = CONVERT_TO_SHORTPTR(ref8);
  uint16_t *comp_pred = CONVERT_TO_SHORTPTR(comp_pred8);
  const uint16_t *src0 = invert_mask ? pred : ref;
  const uint16_t *src1 = invert_mask ? ref : pred;
  const int stride0 = invert_mask ? width : ref_stride;
  const int stride1 = invert_mask ? ref_stride : width;
  const __m256i zero = _mm256_setzero_si256();

  if (width == 8) {
    do {
      const __m256i s0 = mm256_loadu2_16(src0 + stride0, src0);
      const __m256i s1 = mm256_loadu2_16(src1 + stride1, src1);

      const __m128i m_l = _mm_loadl_epi64((const __m128i *)mask);
      const __m128i m_h = _mm_loadl_epi64((const __m128i *)(mask + 8));

      __m256i m = _mm256_castsi128_si256(m_l);
      m = _mm256_insertf128_si256(m, m_h, 1);
      const __m256i m_16 = _mm256_unpacklo_epi8(m, zero);

      const __m256i comp = highbd_comp_mask_pred_line_avx2(s0, s1, m_16);

      _mm_storeu_si128((__m128i *)(comp_pred), _mm256_castsi256_si128(comp));

      _mm_storeu_si128((__m128i *)(comp_pred + width),
                       _mm256_extractf128_si256(comp, 1));

      src0 += (stride0 << 1);
      src1 += (stride1 << 1);
      mask += (mask_stride << 1);
      comp_pred += (width << 1);
      i += 2;
    } while (i < height);
  } else if (width == 16) {
    do {
      const __m256i s0 = _mm256_loadu_si256((const __m256i *)(src0));
      const __m256i s1 = _mm256_loadu_si256((const __m256i *)(src1));
      const __m256i m_16 =
          _mm256_cvtepu8_epi16(_mm_loadu_si128((const __m128i *)mask));

      const __m256i comp = highbd_comp_mask_pred_line_avx2(s0, s1, m_16);

      _mm256_storeu_si256((__m256i *)comp_pred, comp);

      src0 += stride0;
      src1 += stride1;
      mask += mask_stride;
      comp_pred += width;
      i += 1;
    } while (i < height);
  } else if (width == 32) {
    do {
      const __m256i s0 = _mm256_loadu_si256((const __m256i *)src0);
      const __m256i s2 = _mm256_loadu_si256((const __m256i *)(src0 + 16));
      const __m256i s1 = _mm256_loadu_si256((const __m256i *)src1);
      const __m256i s3 = _mm256_loadu_si256((const __m256i *)(src1 + 16));

      const __m256i m01_16 =
          _mm256_cvtepu8_epi16(_mm_loadu_si128((const __m128i *)mask));
      const __m256i m23_16 =
          _mm256_cvtepu8_epi16(_mm_loadu_si128((const __m128i *)(mask + 16)));

      const __m256i comp = highbd_comp_mask_pred_line_avx2(s0, s1, m01_16);
      const __m256i comp1 = highbd_comp_mask_pred_line_avx2(s2, s3, m23_16);

      _mm256_storeu_si256((__m256i *)comp_pred, comp);
      _mm256_storeu_si256((__m256i *)(comp_pred + 16), comp1);

      src0 += stride0;
      src1 += stride1;
      mask += mask_stride;
      comp_pred += width;
      i += 1;
    } while (i < height);
  }
}