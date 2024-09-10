 static inline __m128 gen_05(void)
 {
    __m128i ones = (__m128i)gen_ones();
     return (__m128)_mm_slli_epi32 (_mm_srli_epi32(ones, 26), 24);
 }