sse2_tests (void)
{
  /* psraw */
  c128.v = _mm_srai_epi16 (m128_16, SHIFT);
  dump128_16 (buf, "_mm_srai_epi16", c128);
  c128.v = _mm_sra_epi16 (m128_16, s128);
  dump128_16 (buf, "_mm_sra_epi16", c128);

  /* psrad */
  c128.v = _mm_srai_epi32 (m128_32, SHIFT);
  dump128_32 (buf, "_mm_srai_epi32", c128);
  c128.v = _mm_sra_epi32 (m128_32, s128);
  dump128_32 (buf, "_mm_sra_epi32", c128);

  /* psrlw */
  c128.v = _mm_srli_epi16 (m128_16, SHIFT);
  dump128_16 (buf, "_mm_srli_epi16", c128);
  c128.v = _mm_srl_epi16 (m128_16, s128);
  dump128_16 (buf, "_mm_srl_epi16", c128);

  /* psrld */
  c128.v = _mm_srli_epi32 (m128_32, SHIFT);
  dump128_32 (buf, "_mm_srli_epi32", c128);
  c128.v = _mm_srl_epi32 (m128_32, s128);
  dump128_32 (buf, "_mm_srl_epi32", c128);

  /* psrlq */
  c128.v = _mm_srli_epi64 (m128_64, SHIFT);
  dump128_64 (buf, "_mm_srli_epi64", c128);
  c128.v = _mm_srl_epi64 (m128_64, s128);
  dump128_64 (buf, "_mm_srl_epi64", c128);

  /* psrldq */
  c128.v = _mm_srli_si128 (m128_128, SHIFT);
  dump128_128 (buf, "_mm_srli_si128 (byte shift) ", c128);

  /* psllw */
  c128.v = _mm_slli_epi16 (m128_16, SHIFT);
  dump128_16 (buf, "_mm_slli_epi16", c128);
  c128.v = _mm_sll_epi16 (m128_16, s128);
  dump128_16 (buf, "_mm_sll_epi16", c128);

  /* pslld */
  c128.v = _mm_slli_epi32 (m128_32, SHIFT);
  dump128_32 (buf, "_mm_slli_epi32", c128);
  c128.v = _mm_sll_epi32 (m128_32, s128);
  dump128_32 (buf, "_mm_sll_epi32", c128);

  /* psllq */
  c128.v = _mm_slli_epi64 (m128_64, SHIFT);
  dump128_64 (buf, "_mm_slli_epi64", c128);
  c128.v = _mm_sll_epi64 (m128_64, s128);
  dump128_64 (buf, "_mm_sll_epi64", c128);

  /* pslldq */
  c128.v = _mm_slli_si128 (m128_128, SHIFT);
  dump128_128 (buf, "_mm_sll_si128 (byte shift)", c128);

  /* Shuffle constant 0x1b == 0b_00_01_10_11, e.g. swap words: ABCD => DCBA.  */

  /* pshufd */
  c128.v = _mm_shuffle_epi32 (m128_128, 0x1b);
  dump128_32 (buf, "_mm_shuffle_epi32", c128);

  /* pshuflw */
  c128.v = _mm_shufflelo_epi16 (m128_128, 0x1b);
  dump128_16 (buf, "_mm_shuffelo_epi16", c128);

  /* pshufhw */
  c128.v = _mm_shufflehi_epi16 (m128_128, 0x1b);
  dump128_16 (buf, "_mm_shuffehi_epi16", c128);
}