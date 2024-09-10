void vpx_highbd_d63_predictor_16x16_ssse3(uint16_t *dst, ptrdiff_t stride,
                                          const uint16_t *above,
                                          const uint16_t *left, int bd) {
  const __m128i A0 = _mm_load_si128((const __m128i *)above);
  const __m128i A1 = _mm_load_si128((const __m128i *)(above + 8));
  const __m128i AR0 = _mm_shufflehi_epi16(A1, 0xff);
  const __m128i AR = _mm_unpackhi_epi64(AR0, AR0);
  const __m128i B0 = _mm_alignr_epi8(A1, A0, 2);
  const __m128i B1 = _mm_alignr_epi8(AR, A1, 2);
  const __m128i C0 = _mm_alignr_epi8(A1, A0, 4);
  const __m128i C1 = _mm_alignr_epi8(AR, A1, 4);
  __m128i avg3_0 = avg3_epu16(&A0, &B0, &C0);
  __m128i avg3_1 = avg3_epu16(&A1, &B1, &C1);
  __m128i avg2_0 = _mm_avg_epu16(A0, B0);
  __m128i avg2_1 = _mm_avg_epu16(A1, B1);
  int i;
  (void)left;
  (void)bd;
  for (i = 0; i < 14; i += 2) {
    _mm_store_si128((__m128i *)dst, avg2_0);
    _mm_store_si128((__m128i *)(dst + 8), avg2_1);
    dst += stride;
    _mm_store_si128((__m128i *)dst, avg3_0);
    _mm_store_si128((__m128i *)(dst + 8), avg3_1);
    dst += stride;
    avg2_0 = _mm_alignr_epi8(avg2_1, avg2_0, 2);
    avg2_1 = _mm_alignr_epi8(AR, avg2_1, 2);
    avg3_0 = _mm_alignr_epi8(avg3_1, avg3_0, 2);
    avg3_1 = _mm_alignr_epi8(AR, avg3_1, 2);
  }
  _mm_store_si128((__m128i *)dst, avg2_0);
  _mm_store_si128((__m128i *)(dst + 8), avg2_1);
  dst += stride;
  _mm_store_si128((__m128i *)dst, avg3_0);
  _mm_store_si128((__m128i *)(dst + 8), avg3_1);
}