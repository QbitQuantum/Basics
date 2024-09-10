unsigned int vp9_sub_pixel_variance32xh_avx2(const uint8_t *src,
                                             int src_stride,
                                             int x_offset,
                                             int y_offset,
                                             const uint8_t *dst,
                                             int dst_stride,
                                             int height,
                                             unsigned int *sse) {
  __m256i src_reg, dst_reg, exp_src_lo, exp_src_hi, exp_dst_lo, exp_dst_hi;
  __m256i sse_reg, sum_reg, sse_reg_hi, res_cmp, sum_reg_lo, sum_reg_hi;
  __m256i zero_reg;
  int i, sum;
  sum_reg = _mm256_set1_epi16(0);
  sse_reg = _mm256_set1_epi16(0);
  zero_reg = _mm256_set1_epi16(0);

  // x_offset = 0 and y_offset = 0
  if (x_offset == 0) {
    if (y_offset == 0) {
      for (i = 0; i < height ; i++) {
        LOAD_SRC_DST
        // expend each byte to 2 bytes
        MERGE_WITH_SRC(src_reg, zero_reg)
        CALC_SUM_SSE_INSIDE_LOOP
        src+= src_stride;
        dst+= dst_stride;
      }
    // x_offset = 0 and y_offset = 8
    } else if (y_offset == 8) {
      __m256i src_next_reg;
      for (i = 0; i < height ; i++) {
        LOAD_SRC_DST
        AVG_NEXT_SRC(src_reg, src_stride)
        // expend each byte to 2 bytes
        MERGE_WITH_SRC(src_reg, zero_reg)
        CALC_SUM_SSE_INSIDE_LOOP
        src+= src_stride;
        dst+= dst_stride;
      }
    // x_offset = 0 and y_offset = bilin interpolation
    } else {
      __m256i filter, pw8, src_next_reg;

      y_offset <<= 5;
      filter = _mm256_load_si256((__m256i const *)
               (bilinear_filters_avx2 + y_offset));
      pw8 = _mm256_set1_epi16(8);
      for (i = 0; i < height ; i++) {
        LOAD_SRC_DST
        MERGE_NEXT_SRC(src_reg, src_stride)
        FILTER_SRC(filter)
        CALC_SUM_SSE_INSIDE_LOOP
        src+= src_stride;
        dst+= dst_stride;
      }
    }
  // x_offset = 8  and y_offset = 0
  } else if (x_offset == 8) {
    if (y_offset == 0) {
      __m256i src_next_reg;
      for (i = 0; i < height ; i++) {
        LOAD_SRC_DST
        AVG_NEXT_SRC(src_reg, 1)
        // expand each byte to 2 bytes
        MERGE_WITH_SRC(src_reg, zero_reg)
        CALC_SUM_SSE_INSIDE_LOOP
        src+= src_stride;
        dst+= dst_stride;
      }
    // x_offset = 8  and y_offset = 8
    } else if (y_offset == 8) {
      __m256i src_next_reg, src_avg;
      // load source and another source starting from the next
      // following byte
      src_reg = _mm256_loadu_si256((__m256i const *) (src));
      AVG_NEXT_SRC(src_reg, 1)
      for (i = 0; i < height ; i++) {
        src_avg = src_reg;
        src+= src_stride;
        LOAD_SRC_DST
        AVG_NEXT_SRC(src_reg, 1)
        // average between previous average to current average
        src_avg = _mm256_avg_epu8(src_avg, src_reg);
        // expand each byte to 2 bytes
        MERGE_WITH_SRC(src_avg, zero_reg)
        // save current source average
        CALC_SUM_SSE_INSIDE_LOOP
        dst+= dst_stride;
      }
    // x_offset = 8  and y_offset = bilin interpolation
    } else {