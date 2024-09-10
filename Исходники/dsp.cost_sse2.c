static void SetResidualCoeffsSSE2(const int16_t* const coeffs,
                                  VP8Residual* const res) {
  const __m128i c0 = _mm_loadu_si128((const __m128i*)coeffs);
  const __m128i c1 = _mm_loadu_si128((const __m128i*)(coeffs + 8));
  // Use SSE to compare 8 values with a single instruction.
  const __m128i zero = _mm_setzero_si128();
  const __m128i m0 = _mm_cmpeq_epi16(c0, zero);
  const __m128i m1 = _mm_cmpeq_epi16(c1, zero);
  // Get the comparison results as a bitmask, consisting of two times 16 bits:
  // two identical bits for each result. Concatenate both bitmasks to get a
  // single 32 bit value. Negate the mask to get the position of entries that
  // are not equal to zero. We don't need to mask out least significant bits
  // according to res->first, since coeffs[0] is 0 if res->first > 0
  const uint32_t mask =
      ~(((uint32_t)_mm_movemask_epi8(m1) << 16) | _mm_movemask_epi8(m0));
  // The position of the most significant non-zero bit indicates the position of
  // the last non-zero value. Divide the result by two because __movemask_epi8
  // operates on 8 bit values instead of 16 bit values.
  assert(res->first == 0 || coeffs[0] == 0);
  res->last = mask ? (BitsLog2Floor(mask) >> 1) : -1;
  res->coeffs = coeffs;
}