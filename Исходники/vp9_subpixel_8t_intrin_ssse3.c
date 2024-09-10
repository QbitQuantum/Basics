void vp9_filter_block1d16_v8_intrin_ssse3(unsigned char *src_ptr,
                                          unsigned int src_pitch,
                                          unsigned char *output_ptr,
                                          unsigned int out_pitch,
                                          unsigned int output_height,
                                          int16_t *filter) {
  __m128i addFilterReg64, filtersReg, srcRegFilt1, srcRegFilt2, srcRegFilt3;
  __m128i firstFilters, secondFilters, thirdFilters, forthFilters;
  __m128i srcRegFilt4, srcRegFilt5, srcRegFilt6, srcRegFilt7, srcRegFilt8;
  unsigned int i;

  // create a register with 0,64,0,64,0,64,0,64,0,64,0,64,0,64,0,64
  addFilterReg64 = _mm_set1_epi32((int)0x0400040u);
  filtersReg = _mm_loadu_si128((__m128i *)filter);
  // converting the 16 bit (short) to  8 bit (byte) and have the same data
  // in both lanes of 128 bit register.
  filtersReg =_mm_packs_epi16(filtersReg, filtersReg);

  // duplicate only the first 16 bits in the filter
  firstFilters = _mm_shuffle_epi8(filtersReg, _mm_set1_epi16(0x100u));
  // duplicate only the second 16 bits in the filter
  secondFilters = _mm_shuffle_epi8(filtersReg, _mm_set1_epi16(0x302u));
  // duplicate only the third 16 bits in the filter
  thirdFilters = _mm_shuffle_epi8(filtersReg, _mm_set1_epi16(0x504u));
  // duplicate only the forth 16 bits in the filter
  forthFilters = _mm_shuffle_epi8(filtersReg, _mm_set1_epi16(0x706u));

  for (i = 0; i < output_height; i++) {
    // load the first 16 bytes
    srcRegFilt1 = _mm_loadu_si128((__m128i *)(src_ptr));
    // load the next 16 bytes in stride of src_pitch
    srcRegFilt2 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch));
    srcRegFilt3 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*6));
    srcRegFilt4 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*7));

    // merge the result together
    srcRegFilt5 = _mm_unpacklo_epi8(srcRegFilt1, srcRegFilt2);
    srcRegFilt6 = _mm_unpacklo_epi8(srcRegFilt3, srcRegFilt4);
    srcRegFilt1 = _mm_unpackhi_epi8(srcRegFilt1, srcRegFilt2);
    srcRegFilt3 = _mm_unpackhi_epi8(srcRegFilt3, srcRegFilt4);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt5 = _mm_maddubs_epi16(srcRegFilt5, firstFilters);
    srcRegFilt6 = _mm_maddubs_epi16(srcRegFilt6, forthFilters);
    srcRegFilt1 = _mm_maddubs_epi16(srcRegFilt1, firstFilters);
    srcRegFilt3 = _mm_maddubs_epi16(srcRegFilt3, forthFilters);

    // add and saturate the results together
    srcRegFilt5 = _mm_adds_epi16(srcRegFilt5, srcRegFilt6);
    srcRegFilt1 = _mm_adds_epi16(srcRegFilt1, srcRegFilt3);

    // load the next 16 bytes in stride of two/three src_pitch
    srcRegFilt2 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*2));
    srcRegFilt3 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*3));

    // merge the result together
    srcRegFilt4 = _mm_unpacklo_epi8(srcRegFilt2, srcRegFilt3);
    srcRegFilt6 = _mm_unpackhi_epi8(srcRegFilt2, srcRegFilt3);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt4 = _mm_maddubs_epi16(srcRegFilt4, secondFilters);
    srcRegFilt6 = _mm_maddubs_epi16(srcRegFilt6, secondFilters);

    // load the next 16 bytes in stride of four/five src_pitch
    srcRegFilt2 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*4));
    srcRegFilt3 = _mm_loadu_si128((__m128i *)(src_ptr+src_pitch*5));

    // merge the result together
    srcRegFilt7 = _mm_unpacklo_epi8(srcRegFilt2, srcRegFilt3);
    srcRegFilt8 = _mm_unpackhi_epi8(srcRegFilt2, srcRegFilt3);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt7 = _mm_maddubs_epi16(srcRegFilt7, thirdFilters);
    srcRegFilt8 = _mm_maddubs_epi16(srcRegFilt8, thirdFilters);

    // add and saturate the results together
    srcRegFilt5 = _mm_adds_epi16(srcRegFilt5,
                                 _mm_min_epi16(srcRegFilt4, srcRegFilt7));
    srcRegFilt1 = _mm_adds_epi16(srcRegFilt1,
                                 _mm_min_epi16(srcRegFilt6, srcRegFilt8));

    // add and saturate the results together
    srcRegFilt5 = _mm_adds_epi16(srcRegFilt5,
                                 _mm_max_epi16(srcRegFilt4, srcRegFilt7));
    srcRegFilt1 = _mm_adds_epi16(srcRegFilt1,
                                 _mm_max_epi16(srcRegFilt6, srcRegFilt8));
    srcRegFilt5 = _mm_adds_epi16(srcRegFilt5, addFilterReg64);
    srcRegFilt1 = _mm_adds_epi16(srcRegFilt1, addFilterReg64);

    // shift by 7 bit each 16 bit
    srcRegFilt5 = _mm_srai_epi16(srcRegFilt5, 7);
    srcRegFilt1 = _mm_srai_epi16(srcRegFilt1, 7);

    // shrink to 8 bit each 16 bits, the first lane contain the first
    // convolve result and the second lane contain the second convolve
    // result
    srcRegFilt1 = _mm_packus_epi16(srcRegFilt5, srcRegFilt1);

    src_ptr+=src_pitch;

    // save 16 bytes convolve result
    _mm_store_si128((__m128i*)output_ptr, srcRegFilt1);

    output_ptr+=out_pitch;
  }
}