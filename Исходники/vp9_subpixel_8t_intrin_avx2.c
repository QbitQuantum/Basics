void vp9_filter_block1d16_h8_avx2(unsigned char *src_ptr,
                                  unsigned int src_pixels_per_line,
                                  unsigned char *output_ptr,
                                  unsigned int  output_pitch,
                                  unsigned int  output_height,
                                  int16_t *filter) {
  __m128i filtersReg;
  __m256i addFilterReg64, filt1Reg, filt2Reg, filt3Reg, filt4Reg;
  __m256i firstFilters, secondFilters, thirdFilters, forthFilters;
  __m256i srcRegFilt32b1_1, srcRegFilt32b2_1, srcRegFilt32b2, srcRegFilt32b3;
  __m256i srcReg32b1, srcReg32b2, filtersReg32;
  unsigned int i;
  unsigned int src_stride, dst_stride;

  // create a register with 0,64,0,64,0,64,0,64,0,64,0,64,0,64,0,64
  addFilterReg64 = _mm256_set1_epi32((int)0x0400040u);
  filtersReg = _mm_loadu_si128((__m128i *)filter);
  // converting the 16 bit (short) to 8 bit (byte) and have the same data
  // in both lanes of 128 bit register.
  filtersReg =_mm_packs_epi16(filtersReg, filtersReg);
  // have the same data in both lanes of a 256 bit register
  filtersReg32 = MM256_BROADCASTSI128_SI256(filtersReg);

  // duplicate only the first 16 bits (first and second byte)
  // across 256 bit register
  firstFilters = _mm256_shuffle_epi8(filtersReg32,
                 _mm256_set1_epi16(0x100u));
  // duplicate only the second 16 bits (third and forth byte)
  // across 256 bit register
  secondFilters = _mm256_shuffle_epi8(filtersReg32,
                  _mm256_set1_epi16(0x302u));
  // duplicate only the third 16 bits (fifth and sixth byte)
  // across 256 bit register
  thirdFilters = _mm256_shuffle_epi8(filtersReg32,
                 _mm256_set1_epi16(0x504u));
  // duplicate only the forth 16 bits (seventh and eighth byte)
  // across 256 bit register
  forthFilters = _mm256_shuffle_epi8(filtersReg32,
                 _mm256_set1_epi16(0x706u));

  filt1Reg = _mm256_load_si256((__m256i const *)filt1_global_avx2);
  filt2Reg = _mm256_load_si256((__m256i const *)filt2_global_avx2);
  filt3Reg = _mm256_load_si256((__m256i const *)filt3_global_avx2);
  filt4Reg = _mm256_load_si256((__m256i const *)filt4_global_avx2);

  // multiple the size of the source and destination stride by two
  src_stride = src_pixels_per_line << 1;
  dst_stride = output_pitch << 1;
  for (i = output_height; i > 1; i-=2) {
    // load the 2 strides of source
    srcReg32b1 = _mm256_castsi128_si256(
                 _mm_loadu_si128((__m128i *)(src_ptr-3)));
    srcReg32b1 = _mm256_inserti128_si256(srcReg32b1,
                 _mm_loadu_si128((__m128i *)
                 (src_ptr+src_pixels_per_line-3)), 1);

    // filter the source buffer
    srcRegFilt32b1_1= _mm256_shuffle_epi8(srcReg32b1, filt1Reg);
    srcRegFilt32b2= _mm256_shuffle_epi8(srcReg32b1, filt4Reg);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt32b1_1 = _mm256_maddubs_epi16(srcRegFilt32b1_1, firstFilters);
    srcRegFilt32b2 = _mm256_maddubs_epi16(srcRegFilt32b2, forthFilters);

    // add and saturate the results together
    srcRegFilt32b1_1 = _mm256_adds_epi16(srcRegFilt32b1_1, srcRegFilt32b2);

    // filter the source buffer
    srcRegFilt32b3= _mm256_shuffle_epi8(srcReg32b1, filt2Reg);
    srcRegFilt32b2= _mm256_shuffle_epi8(srcReg32b1, filt3Reg);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt32b3 = _mm256_maddubs_epi16(srcRegFilt32b3, secondFilters);
    srcRegFilt32b2 = _mm256_maddubs_epi16(srcRegFilt32b2, thirdFilters);

    // add and saturate the results together
    srcRegFilt32b1_1 = _mm256_adds_epi16(srcRegFilt32b1_1,
                       _mm256_min_epi16(srcRegFilt32b3, srcRegFilt32b2));

    // reading 2 strides of the next 16 bytes
    // (part of it was being read by earlier read)
    srcReg32b2 = _mm256_castsi128_si256(
                 _mm_loadu_si128((__m128i *)(src_ptr+5)));
    srcReg32b2 = _mm256_inserti128_si256(srcReg32b2,
                 _mm_loadu_si128((__m128i *)
                 (src_ptr+src_pixels_per_line+5)), 1);

    // add and saturate the results together
    srcRegFilt32b1_1 = _mm256_adds_epi16(srcRegFilt32b1_1,
                       _mm256_max_epi16(srcRegFilt32b3, srcRegFilt32b2));

    // filter the source buffer
    srcRegFilt32b2_1 = _mm256_shuffle_epi8(srcReg32b2, filt1Reg);
    srcRegFilt32b2 = _mm256_shuffle_epi8(srcReg32b2, filt4Reg);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt32b2_1 = _mm256_maddubs_epi16(srcRegFilt32b2_1, firstFilters);
    srcRegFilt32b2 = _mm256_maddubs_epi16(srcRegFilt32b2, forthFilters);

    // add and saturate the results together
    srcRegFilt32b2_1 = _mm256_adds_epi16(srcRegFilt32b2_1, srcRegFilt32b2);

    // filter the source buffer
    srcRegFilt32b3= _mm256_shuffle_epi8(srcReg32b2, filt2Reg);
    srcRegFilt32b2= _mm256_shuffle_epi8(srcReg32b2, filt3Reg);

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt32b3 = _mm256_maddubs_epi16(srcRegFilt32b3, secondFilters);
    srcRegFilt32b2 = _mm256_maddubs_epi16(srcRegFilt32b2, thirdFilters);

    // add and saturate the results together
    srcRegFilt32b2_1 = _mm256_adds_epi16(srcRegFilt32b2_1,
                       _mm256_min_epi16(srcRegFilt32b3, srcRegFilt32b2));
    srcRegFilt32b2_1 = _mm256_adds_epi16(srcRegFilt32b2_1,
                       _mm256_max_epi16(srcRegFilt32b3, srcRegFilt32b2));


    srcRegFilt32b1_1 = _mm256_adds_epi16(srcRegFilt32b1_1, addFilterReg64);

    srcRegFilt32b2_1 = _mm256_adds_epi16(srcRegFilt32b2_1, addFilterReg64);

    // shift by 7 bit each 16 bit
    srcRegFilt32b1_1 = _mm256_srai_epi16(srcRegFilt32b1_1, 7);
    srcRegFilt32b2_1 = _mm256_srai_epi16(srcRegFilt32b2_1, 7);

    // shrink to 8 bit each 16 bits, the first lane contain the first
    // convolve result and the second lane contain the second convolve
    // result
    srcRegFilt32b1_1 = _mm256_packus_epi16(srcRegFilt32b1_1,
                                           srcRegFilt32b2_1);

    src_ptr+=src_stride;

    // save 16 bytes
    _mm_store_si128((__m128i*)output_ptr,
    _mm256_castsi256_si128(srcRegFilt32b1_1));

    // save the next 16 bits
    _mm_store_si128((__m128i*)(output_ptr+output_pitch),
    _mm256_extractf128_si256(srcRegFilt32b1_1, 1));
    output_ptr+=dst_stride;
  }

  // if the number of strides is odd.
  // process only 16 bytes
  if (i > 0) {
    __m128i srcReg1, srcReg2, srcRegFilt1_1, srcRegFilt2_1;
    __m128i srcRegFilt2, srcRegFilt3;

    srcReg1 = _mm_loadu_si128((__m128i *)(src_ptr-3));

    // filter the source buffer
    srcRegFilt1_1 = _mm_shuffle_epi8(srcReg1,
                    _mm256_castsi256_si128(filt1Reg));
    srcRegFilt2 = _mm_shuffle_epi8(srcReg1,
                  _mm256_castsi256_si128(filt4Reg));

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt1_1 = _mm_maddubs_epi16(srcRegFilt1_1,
                    _mm256_castsi256_si128(firstFilters));
    srcRegFilt2 = _mm_maddubs_epi16(srcRegFilt2,
                  _mm256_castsi256_si128(forthFilters));

    // add and saturate the results together
    srcRegFilt1_1 = _mm_adds_epi16(srcRegFilt1_1, srcRegFilt2);

    // filter the source buffer
    srcRegFilt3= _mm_shuffle_epi8(srcReg1,
                 _mm256_castsi256_si128(filt2Reg));
    srcRegFilt2= _mm_shuffle_epi8(srcReg1,
                 _mm256_castsi256_si128(filt3Reg));

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt3 = _mm_maddubs_epi16(srcRegFilt3,
                  _mm256_castsi256_si128(secondFilters));
    srcRegFilt2 = _mm_maddubs_epi16(srcRegFilt2,
                  _mm256_castsi256_si128(thirdFilters));

    // add and saturate the results together
    srcRegFilt1_1 = _mm_adds_epi16(srcRegFilt1_1,
                    _mm_min_epi16(srcRegFilt3, srcRegFilt2));

    // reading the next 16 bytes
    // (part of it was being read by earlier read)
    srcReg2 = _mm_loadu_si128((__m128i *)(src_ptr+5));

    // add and saturate the results together
    srcRegFilt1_1 = _mm_adds_epi16(srcRegFilt1_1,
                    _mm_max_epi16(srcRegFilt3, srcRegFilt2));

    // filter the source buffer
    srcRegFilt2_1 = _mm_shuffle_epi8(srcReg2,
                    _mm256_castsi256_si128(filt1Reg));
    srcRegFilt2 = _mm_shuffle_epi8(srcReg2,
                  _mm256_castsi256_si128(filt4Reg));

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt2_1 = _mm_maddubs_epi16(srcRegFilt2_1,
                    _mm256_castsi256_si128(firstFilters));
    srcRegFilt2 = _mm_maddubs_epi16(srcRegFilt2,
                  _mm256_castsi256_si128(forthFilters));

    // add and saturate the results together
    srcRegFilt2_1 = _mm_adds_epi16(srcRegFilt2_1, srcRegFilt2);

    // filter the source buffer
    srcRegFilt3 = _mm_shuffle_epi8(srcReg2,
                  _mm256_castsi256_si128(filt2Reg));
    srcRegFilt2 = _mm_shuffle_epi8(srcReg2,
                  _mm256_castsi256_si128(filt3Reg));

    // multiply 2 adjacent elements with the filter and add the result
    srcRegFilt3 = _mm_maddubs_epi16(srcRegFilt3,
                  _mm256_castsi256_si128(secondFilters));
    srcRegFilt2 = _mm_maddubs_epi16(srcRegFilt2,
                  _mm256_castsi256_si128(thirdFilters));

    // add and saturate the results together
    srcRegFilt2_1 = _mm_adds_epi16(srcRegFilt2_1,
                    _mm_min_epi16(srcRegFilt3, srcRegFilt2));
    srcRegFilt2_1 = _mm_adds_epi16(srcRegFilt2_1,
                    _mm_max_epi16(srcRegFilt3, srcRegFilt2));


    srcRegFilt1_1 = _mm_adds_epi16(srcRegFilt1_1,
                    _mm256_castsi256_si128(addFilterReg64));

    srcRegFilt2_1 = _mm_adds_epi16(srcRegFilt2_1,
                    _mm256_castsi256_si128(addFilterReg64));

    // shift by 7 bit each 16 bit
    srcRegFilt1_1 = _mm_srai_epi16(srcRegFilt1_1, 7);
    srcRegFilt2_1 = _mm_srai_epi16(srcRegFilt2_1, 7);

    // shrink to 8 bit each 16 bits, the first lane contain the first
    // convolve result and the second lane contain the second convolve
    // result
    srcRegFilt1_1 = _mm_packus_epi16(srcRegFilt1_1, srcRegFilt2_1);

    // save 16 bytes
    _mm_store_si128((__m128i*)output_ptr, srcRegFilt1_1);
  }
}