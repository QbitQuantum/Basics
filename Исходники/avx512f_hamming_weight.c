static void CSA(__m512i* h, __m512i* l, __m512i a, __m512i b, __m512i c) {

  *l = _mm512_ternarylogic_epi32(c, b, a, 0x96);
  *h = _mm512_ternarylogic_epi32(c, b, a, 0xe8);
}