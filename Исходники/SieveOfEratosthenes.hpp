  static FORCEINLINE uint64_t getNextPrime(uint64_t* bits, uint64_t base)
  {
	  // calculate bitValues_[ bitScanForward(*bits) ]
	  // using a custom De Bruijn bitscan
	  //uint64_t debruijn64 = UINT64_C(0x3F08A4C6ACB9DBD);
	  uint64_t mask = *bits - 1;
	  //uint64_t bitValue = bruijnBitValues_[((*bits ^ mask) * debruijn64) >> 58];
	  //uint64_t prime = base + bitValue;
	  unsigned long index;
	  _BitScanForward64(&index, *bits);
	  uint64_t prime = base + bitValuesRaw_[index];
	  *bits &= mask;
	  return prime;
  }