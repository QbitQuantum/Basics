// Special case for left-based prediction (when preds==dst-1 or preds==src-1).
static void PredictLineLeft(const uint8_t* src, uint8_t* dst, int length,
                            int inverse) {
  int i;
  if (length <= 0) return;
  if (inverse) {
    const int max_pos = length & ~7;
    __m128i last = _mm_set_epi32(0, 0, 0, dst[-1]);
    for (i = 0; i < max_pos; i += 8) {
      const __m128i A0 = _mm_loadl_epi64((const __m128i*)(src + i));
      const __m128i A1 = _mm_add_epi8(A0, last);
      const __m128i A2 = _mm_slli_si128(A1, 1);
      const __m128i A3 = _mm_add_epi8(A1, A2);
      const __m128i A4 = _mm_slli_si128(A3, 2);
      const __m128i A5 = _mm_add_epi8(A3, A4);
      const __m128i A6 = _mm_slli_si128(A5, 4);
      const __m128i A7 = _mm_add_epi8(A5, A6);
      _mm_storel_epi64((__m128i*)(dst + i), A7);
      last = _mm_srli_epi64(A7, 56);
    }
    for (; i < length; ++i) dst[i] = src[i] + dst[i - 1];
  } else {
    const int max_pos = length & ~31;
    for (i = 0; i < max_pos; i += 32) {
      const __m128i A0 = _mm_loadu_si128((const __m128i*)(src + i +  0    ));
      const __m128i B0 = _mm_loadu_si128((const __m128i*)(src + i +  0 - 1));
      const __m128i A1 = _mm_loadu_si128((const __m128i*)(src + i + 16    ));
      const __m128i B1 = _mm_loadu_si128((const __m128i*)(src + i + 16 - 1));
      const __m128i C0 = _mm_sub_epi8(A0, B0);
      const __m128i C1 = _mm_sub_epi8(A1, B1);
      _mm_storeu_si128((__m128i*)(dst + i +  0), C0);
      _mm_storeu_si128((__m128i*)(dst + i + 16), C1);
    }
    for (; i < length; ++i) dst[i] = src[i] - src[i - 1];
  }
}