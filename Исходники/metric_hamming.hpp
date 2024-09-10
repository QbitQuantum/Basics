  inline ResultType operator()(Iterator1 a, Iterator2 b, size_t size) const
  {
    ResultType result = 0;
#if (defined __GNUC__ || defined __clang__) && defined USE_SSE
#ifdef __ARM_NEON__
    {
      uint32x4_t bits = vmovq_n_u32(0);
      for (size_t i = 0; i < size; i += 16) {
        uint8x16_t A_vec = vld1q_u8 (a + i);
        uint8x16_t B_vec = vld1q_u8 (b + i);
        uint8x16_t AxorB = veorq_u8 (A_vec, B_vec);
        uint8x16_t bitsSet = vcntq_u8 (AxorB);
        uint16x8_t bitSet8 = vpaddlq_u8 (bitsSet);
        uint32x4_t bitSet4 = vpaddlq_u16 (bitSet8);
        bits = vaddq_u32(bits, bitSet4);
      }
      uint64x2_t bitSet2 = vpaddlq_u32 (bits);
      result = vgetq_lane_s32 (vreinterpretq_s32_u64(bitSet2),0);
      result += vgetq_lane_s32 (vreinterpretq_s32_u64(bitSet2),2);
    }
#else
    {
      //for portability just use unsigned long -- and use the __builtin_popcountll (see docs for __builtin_popcountll)
      typedef unsigned long long pop_t;
      const size_t modulo = size % sizeof(pop_t);
      const pop_t* a2 = reinterpret_cast<const pop_t*> (a);
      const pop_t* b2 = reinterpret_cast<const pop_t*> (b);
      const pop_t* a2_end = a2 + (size / sizeof(pop_t));

      for (; a2 != a2_end; ++a2, ++b2) result += __builtin_popcountll((*a2) ^ (*b2));

      if (modulo) {
        //in the case where size is not dividable by sizeof(pop_t)
        //need to mask off the bits at the end
        pop_t a_final = 0, b_final = 0;
        memcpy(&a_final, a2, modulo);
        memcpy(&b_final, b2, modulo);
        result += __builtin_popcountll(a_final ^ b_final);
      }
    }
#endif //NEON
    return result;
#endif
#ifdef PLATFORM_64_BIT
    if(size%64 == 0)
    {
      const uint64_t* pa = reinterpret_cast<const uint64_t*>(a);
      const uint64_t* pb = reinterpret_cast<const uint64_t*>(b);
      size /= (sizeof(uint64_t)/sizeof(unsigned char));
      for(size_t i = 0; i < size; ++i, ++pa, ++pb ) {
        result += popcnt64(*pa ^ *pb);
      }
    }
    else
    {
      const uint32_t* pa = reinterpret_cast<const uint32_t*>(a);
      const uint32_t* pb = reinterpret_cast<const uint32_t*>(b);
      size /= (sizeof(uint32_t)/sizeof(unsigned char));
      for(size_t i = 0; i < size; ++i, ++pa, ++pb ) {
        result += popcnt32(*pa ^ *pb);
      }
    }
#else
    const uint32_t* pa = reinterpret_cast<const uint32_t*>(a);
    const uint32_t* pb = reinterpret_cast<const uint32_t*>(b);
    size /= (sizeof(uint32_t)/sizeof(unsigned char));
    for(size_t i = 0; i < size; ++i, ++pa, ++pb ) {
      result += popcnt32(*pa ^ *pb);
    }
#endif
    return result;
  }