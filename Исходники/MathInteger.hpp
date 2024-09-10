 inline uint popCount(uint64_t value)
 {
     return static_cast<uint>(_mm_popcnt_u64(value));
 }