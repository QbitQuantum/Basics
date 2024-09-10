 __INTRIN_INLINE uint64_t popcount(uint64_t x)
 {
     return uint64_t(_mm_popcnt_u64(x));
 }