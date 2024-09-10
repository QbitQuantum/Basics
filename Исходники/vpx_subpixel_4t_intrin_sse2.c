static void vpx_filter_block1d8_h4_sse2(const uint8_t *src_ptr,
                                        ptrdiff_t src_stride, uint8_t *dst_ptr,
                                        ptrdiff_t dst_stride, uint32_t height,
                                        const int16_t *kernel) {
  __m128i kernel_reg;                         // Kernel
  __m128i kernel_reg_23, kernel_reg_45;       // Segments of the kernel used
  const __m128i reg_32 = _mm_set1_epi16(32);  // Used for rounding
  int h;

  __m128i src_reg, src_reg_shift_1, src_reg_shift_2, src_reg_shift_3;
  __m128i dst_first;
  __m128i even, odd;

  // Start one pixel before as we need tap/2 - 1 = 1 sample from the past
  src_ptr -= 1;

  // Load Kernel
  kernel_reg = _mm_loadu_si128((const __m128i *)kernel);
  kernel_reg = _mm_srai_epi16(kernel_reg, 1);
  kernel_reg_23 = extract_quarter_2_epi16_sse2(&kernel_reg);
  kernel_reg_45 = extract_quarter_3_epi16_sse2(&kernel_reg);

  for (h = height; h > 0; --h) {
    // We will load multiple shifted versions of the row and shuffle them into
    // 16-bit words of the form
    // ... s[2] s[1] s[0] s[-1]
    // ... s[4] s[3] s[2] s[1]
    // Then we call multiply and add to get partial results
    // s[2]k[3]+s[1]k[2] s[0]k[3]s[-1]k[2]
    // s[4]k[5]+s[3]k[4] s[2]k[5]s[1]k[4]
    // The two results are then added together to get the even output
    src_reg = _mm_loadu_si128((const __m128i *)src_ptr);
    src_reg_shift_1 = _mm_srli_si128(src_reg, 1);
    src_reg_shift_2 = _mm_srli_si128(src_reg, 2);
    src_reg_shift_3 = _mm_srli_si128(src_reg, 3);

    // Output 6 4 2 0
    even = mm_madd_add_epi8_sse2(&src_reg, &src_reg_shift_2, &kernel_reg_23,
                                 &kernel_reg_45);

    // Output 7 5 3 1
    odd = mm_madd_add_epi8_sse2(&src_reg_shift_1, &src_reg_shift_3,
                                &kernel_reg_23, &kernel_reg_45);

    // Combine to get the first half of the dst
    dst_first = mm_zip_epi32_sse2(&even, &odd);
    dst_first = mm_round_epi16_sse2(&dst_first, &reg_32, 6);

    // Saturate and convert to 8-bit words
    dst_first = _mm_packus_epi16(dst_first, _mm_setzero_si128());

    _mm_storel_epi64((__m128i *)dst_ptr, dst_first);

    src_ptr += src_stride;
    dst_ptr += dst_stride;
  }
}