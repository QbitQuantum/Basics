static void filter_vert_w16_ssse3(const uint8_t *src_ptr, ptrdiff_t src_pitch,
                                  uint8_t *dst, const int16_t *filter, int w) {
  const __m128i k_256 = _mm_set1_epi16(1 << 8);
  const __m128i f_values = _mm_load_si128((const __m128i *)filter);
  // pack and duplicate the filter values
  const __m128i f1f0 = _mm_shuffle_epi8(f_values, _mm_set1_epi16(0x0200u));
  const __m128i f3f2 = _mm_shuffle_epi8(f_values, _mm_set1_epi16(0x0604u));
  const __m128i f5f4 = _mm_shuffle_epi8(f_values, _mm_set1_epi16(0x0a08u));
  const __m128i f7f6 = _mm_shuffle_epi8(f_values, _mm_set1_epi16(0x0e0cu));
  int i;

  for (i = 0; i < w; i += 16) {
    const __m128i A = _mm_loadu_si128((const __m128i *)src_ptr);
    const __m128i B = _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch));
    const __m128i C =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 2));
    const __m128i D =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 3));
    const __m128i E =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 4));
    const __m128i F =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 5));
    const __m128i G =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 6));
    const __m128i H =
        _mm_loadu_si128((const __m128i *)(src_ptr + src_pitch * 7));
    // merge the result together
    const __m128i s1s0_lo = _mm_unpacklo_epi8(A, B);
    const __m128i s7s6_lo = _mm_unpacklo_epi8(G, H);
    const __m128i s1s0_hi = _mm_unpackhi_epi8(A, B);
    const __m128i s7s6_hi = _mm_unpackhi_epi8(G, H);
    // multiply 2 adjacent elements with the filter and add the result
    const __m128i x0_lo = _mm_maddubs_epi16(s1s0_lo, f1f0);
    const __m128i x3_lo = _mm_maddubs_epi16(s7s6_lo, f7f6);
    const __m128i x0_hi = _mm_maddubs_epi16(s1s0_hi, f1f0);
    const __m128i x3_hi = _mm_maddubs_epi16(s7s6_hi, f7f6);
    // add and saturate the results together
    const __m128i x3x0_lo = _mm_adds_epi16(x0_lo, x3_lo);
    const __m128i x3x0_hi = _mm_adds_epi16(x0_hi, x3_hi);
    // merge the result together
    const __m128i s3s2_lo = _mm_unpacklo_epi8(C, D);
    const __m128i s3s2_hi = _mm_unpackhi_epi8(C, D);
    // multiply 2 adjacent elements with the filter and add the result
    const __m128i x1_lo = _mm_maddubs_epi16(s3s2_lo, f3f2);
    const __m128i x1_hi = _mm_maddubs_epi16(s3s2_hi, f3f2);
    // merge the result together
    const __m128i s5s4_lo = _mm_unpacklo_epi8(E, F);
    const __m128i s5s4_hi = _mm_unpackhi_epi8(E, F);
    // multiply 2 adjacent elements with the filter and add the result
    const __m128i x2_lo = _mm_maddubs_epi16(s5s4_lo, f5f4);
    const __m128i x2_hi = _mm_maddubs_epi16(s5s4_hi, f5f4);
    // add and saturate the results together
    __m128i temp_lo = _mm_adds_epi16(x3x0_lo, _mm_min_epi16(x1_lo, x2_lo));
    __m128i temp_hi = _mm_adds_epi16(x3x0_hi, _mm_min_epi16(x1_hi, x2_hi));

    // add and saturate the results together
    temp_lo = _mm_adds_epi16(temp_lo, _mm_max_epi16(x1_lo, x2_lo));
    temp_hi = _mm_adds_epi16(temp_hi, _mm_max_epi16(x1_hi, x2_hi));
    // round and shift by 7 bit each 16 bit
    temp_lo = _mm_mulhrs_epi16(temp_lo, k_256);
    temp_hi = _mm_mulhrs_epi16(temp_hi, k_256);
    // shrink to 8 bit each 16 bits, the first lane contain the first
    // convolve result and the second lane contain the second convolve
    // result
    temp_hi = _mm_packus_epi16(temp_lo, temp_hi);
    src_ptr += 16;
    // save 16 bytes convolve result
    _mm_store_si128((__m128i *)&dst[i], temp_hi);
  }
}