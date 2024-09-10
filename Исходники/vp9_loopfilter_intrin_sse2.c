                                       int p,
                                       const unsigned char *_blimit,
                                       const unsigned char *_limit,
                                       const unsigned char *_thresh) {
  DECLARE_ALIGNED(16, unsigned char, flat2_op[7][8]);
  DECLARE_ALIGNED(16, unsigned char, flat2_oq[7][8]);

  DECLARE_ALIGNED(16, unsigned char, flat_op[3][8]);
  DECLARE_ALIGNED(16, unsigned char, flat_oq[3][8]);

  DECLARE_ALIGNED(16, unsigned char, ap[8][8]);
  DECLARE_ALIGNED(16, unsigned char, aq[8][8]);


  __m128i mask, hev, flat, flat2;
  const __m128i zero = _mm_set1_epi16(0);
  const __m128i one = _mm_set1_epi8(1);
  __m128i p7, p6, p5;
  __m128i p4, p3, p2, p1, p0, q0, q1, q2, q3, q4;
  __m128i q5, q6, q7;
  int i = 0;
  const unsigned int extended_thresh = _thresh[0] * 0x01010101u;
  const unsigned int extended_limit  = _limit[0]  * 0x01010101u;
  const unsigned int extended_blimit = _blimit[0] * 0x01010101u;
  const __m128i thresh =
      _mm_shuffle_epi32(_mm_cvtsi32_si128((int)extended_thresh), 0);
  const __m128i limit =
      _mm_shuffle_epi32(_mm_cvtsi32_si128((int)extended_limit), 0);
  const __m128i blimit =
      _mm_shuffle_epi32(_mm_cvtsi32_si128((int)extended_blimit), 0);
