SSE_FUNCTION static void
sad8x8_u8_sse (uint32_t *dest, uint8_t *src1, int sstr1, uint8_t *src2,
    int sstr2)
{
  int i;
  __m128i sum = _mm_setzero_si128();
  union m128_int sumi;

  for (i = 0; i < 4; i++) {
    __m128i xmm0, xmm1, xmm2, xmm3;
    xmm0 = _mm_loadl_epi64((__m128i *)src1);
    xmm1 = _mm_loadl_epi64((__m128i *)(src1 + sstr1));
    xmm2 = _mm_loadl_epi64((__m128i *)src2);
    xmm3 = _mm_loadl_epi64((__m128i *)(src2 + sstr2));
    xmm0 = _mm_unpacklo_epi8(xmm0, xmm1);
    xmm2 = _mm_unpacklo_epi8(xmm2, xmm3);
    sum = _mm_add_epi64(sum, _mm_sad_epu8(xmm0, xmm2));
    src1 += 2 * sstr1;
    src2 += 2 * sstr2;
  }
  sumi.m128 = sum;
  *dest = sumi.i[0] + sumi.i[2];
}