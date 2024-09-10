uint32_t
crc32_hw_aligned(uint32_t remainder, const __m128i* p, size_t vec_count) {
  /* Constants precomputed by gen_crc32_multipliers.c.  Do not edit! */
  const __m128i multipliers_4 = _mm_set_epi32(0, 0x1D9513D7, 0, 0x8F352D95);
  const __m128i multipliers_2 = _mm_set_epi32(0, 0x81256527, 0, 0xF1DA05AA);
  const __m128i multipliers_1 = _mm_set_epi32(0, 0xCCAA009E, 0, 0xAE689191);
  const __m128i final_multiplier = _mm_set_epi32(0, 0, 0, 0xB8BC6765);
  const __m128i mask32 = _mm_set_epi32(0, 0, 0, 0xFFFFFFFF);
  const __m128i barrett_reduction_constants =
      _mm_set_epi32(0x1, 0xDB710641, 0x1, 0xF7011641);

  const __m128i* const end = p + vec_count;
  const __m128i* const end512 = p + (vec_count & ~3);
  __m128i x0, x1, x2, x3;

  /*
   * Account for the current 'remainder', i.e. the CRC of the part of
   * the message already processed.  Explanation: rewrite the message
   * polynomial M(x) in terms of the first part A(x), the second part
   * B(x), and the length of the second part in bits |B(x)| >= 32:
   *
   *    M(x) = A(x)*x^|B(x)| + B(x)
   *
   * Then the CRC of M(x) is:
   *
   *    CRC(M(x)) = CRC(A(x)*x^|B(x)| + B(x))
   *              = CRC(A(x)*x^32*x^(|B(x)| - 32) + B(x))
   *              = CRC(CRC(A(x))*x^(|B(x)| - 32) + B(x))
   *
   * Note: all arithmetic is modulo G(x), the generator polynomial; that's
   * why A(x)*x^32 can be replaced with CRC(A(x)) = A(x)*x^32 mod G(x).
   *
   * So the CRC of the full message is the CRC of the second part of the
   * message where the first 32 bits of the second part of the message
   * have been XOR'ed with the CRC of the first part of the message.
   */
  x0 = *p++;
  x0 = _mm_xor_si128(x0, _mm_set_epi32(0, 0, 0, remainder));

  if (p > end512) /* only 128, 256, or 384 bits of input? */
    goto _128_bits_at_a_time;
  x1 = *p++;
  x2 = *p++;
  x3 = *p++;

  /* Fold 512 bits at a time */
  for (; p != end512; p += 4) {
    __m128i y0, y1, y2, y3;

    y0 = p[0];
    y1 = p[1];
    y2 = p[2];
    y3 = p[3];

    /*
     * Note: the immediate constant for PCLMULQDQ specifies which
     * 64-bit halves of the 128-bit vectors to multiply:
     *
     * 0x00 means low halves (higher degree polynomial terms for us)
     * 0x11 means high halves (lower degree polynomial terms for us)
     */
    y0 = _mm_xor_si128(y0, _mm_clmulepi64_si128(x0, multipliers_4, 0x00));
    y1 = _mm_xor_si128(y1, _mm_clmulepi64_si128(x1, multipliers_4, 0x00));
    y2 = _mm_xor_si128(y2, _mm_clmulepi64_si128(x2, multipliers_4, 0x00));
    y3 = _mm_xor_si128(y3, _mm_clmulepi64_si128(x3, multipliers_4, 0x00));
    y0 = _mm_xor_si128(y0, _mm_clmulepi64_si128(x0, multipliers_4, 0x11));
    y1 = _mm_xor_si128(y1, _mm_clmulepi64_si128(x1, multipliers_4, 0x11));
    y2 = _mm_xor_si128(y2, _mm_clmulepi64_si128(x2, multipliers_4, 0x11));
    y3 = _mm_xor_si128(y3, _mm_clmulepi64_si128(x3, multipliers_4, 0x11));

    x0 = y0;
    x1 = y1;
    x2 = y2;
    x3 = y3;
  }

  /* Fold 512 bits => 128 bits */
  x2 = _mm_xor_si128(x2, _mm_clmulepi64_si128(x0, multipliers_2, 0x00));
  x3 = _mm_xor_si128(x3, _mm_clmulepi64_si128(x1, multipliers_2, 0x00));
  x2 = _mm_xor_si128(x2, _mm_clmulepi64_si128(x0, multipliers_2, 0x11));
  x3 = _mm_xor_si128(x3, _mm_clmulepi64_si128(x1, multipliers_2, 0x11));
  x3 = _mm_xor_si128(x3, _mm_clmulepi64_si128(x2, multipliers_1, 0x00));
  x3 = _mm_xor_si128(x3, _mm_clmulepi64_si128(x2, multipliers_1, 0x11));
  x0 = x3;

_128_bits_at_a_time:
  while (p != end) {
    /* Fold 128 bits into next 128 bits */
    x1 = *p++;
    x1 = _mm_xor_si128(x1, _mm_clmulepi64_si128(x0, multipliers_1, 0x00));
    x1 = _mm_xor_si128(x1, _mm_clmulepi64_si128(x0, multipliers_1, 0x11));
    x0 = x1;
  }

  /* Now there are just 128 bits left, stored in 'x0'. */

  /*
   * Fold 128 => 96 bits.  This also implicitly appends 32 zero bits,
   * which is equivalent to multiplying by x^32.  This is needed because
   * the CRC is defined as M(x)*x^32 mod G(x), not just M(x) mod G(x).
   */
  x0 = _mm_xor_si128(_mm_srli_si128(x0, 8), _mm_clmulepi64_si128(x0, multipliers_1, 0x10));

  /* Fold 96 => 64 bits */
  x0 = _mm_xor_si128(_mm_srli_si128(x0, 4),
      _mm_clmulepi64_si128(_mm_and_si128(x0, mask32), final_multiplier, 0x00));

  /*
   * Finally, reduce 64 => 32 bits using Barrett reduction.
   *
   * Let M(x) = A(x)*x^32 + B(x) be the remaining message.  The goal is to
   * compute R(x) = M(x) mod G(x).  Since degree(B(x)) < degree(G(x)):
   *
   *    R(x) = (A(x)*x^32 + B(x)) mod G(x)
   *         = (A(x)*x^32) mod G(x) + B(x)
   *
   * Then, by the Division Algorithm there exists a unique q(x) such that:
   *
   *    A(x)*x^32 mod G(x) = A(x)*x^32 - q(x)*G(x)
   *
   * Since the left-hand side is of maximum degree 31, the right-hand side
   * must be too.  This implies that we can apply 'mod x^32' to the
   * right-hand side without changing its value:
   *
   *    (A(x)*x^32 - q(x)*G(x)) mod x^32 = q(x)*G(x) mod x^32
   *
   * Note that '+' is equivalent to '-' in polynomials over GF(2).
   *
   * We also know that:
   *
   *                  / A(x)*x^32 \
   *    q(x) = floor (  ---------  )
   *                  \    G(x)   /
   *
   * To compute this efficiently, we can multiply the top and bottom by
   * x^32 and move the division by G(x) to the top:
   *
   *                  / A(x) * floor(x^64 / G(x)) \
   *    q(x) = floor (  -------------------------  )
   *                  \           x^32            /
   *
   * Note that floor(x^64 / G(x)) is a constant.
   *
   * So finally we have:
   *
   *                              / A(x) * floor(x^64 / G(x)) \
   *    R(x) = B(x) + G(x)*floor (  -------------------------  )
   *                              \           x^32            /
   */
  x1 = x0;
  x0 = _mm_clmulepi64_si128(_mm_and_si128(x0, mask32), barrett_reduction_constants, 0x00);
  x0 = _mm_clmulepi64_si128(_mm_and_si128(x0, mask32), barrett_reduction_constants, 0x10);
  return _mm_cvtsi128_si32(_mm_srli_si128(_mm_xor_si128(x0, x1), 4));
}