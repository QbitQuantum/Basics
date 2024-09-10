static int SSE4x4(const uint8_t* a, const uint8_t* b) {
  const __m128i zero = _mm_setzero_si128();

  // Load values. Note that we read 8 pixels instead of 4,
  // but the a/b buffers are over-allocated to that effect.
  const __m128i a0 = _mm_loadl_epi64((const __m128i*)&a[BPS * 0]);
  const __m128i a1 = _mm_loadl_epi64((const __m128i*)&a[BPS * 1]);
  const __m128i a2 = _mm_loadl_epi64((const __m128i*)&a[BPS * 2]);
  const __m128i a3 = _mm_loadl_epi64((const __m128i*)&a[BPS * 3]);
  const __m128i b0 = _mm_loadl_epi64((const __m128i*)&b[BPS * 0]);
  const __m128i b1 = _mm_loadl_epi64((const __m128i*)&b[BPS * 1]);
  const __m128i b2 = _mm_loadl_epi64((const __m128i*)&b[BPS * 2]);
  const __m128i b3 = _mm_loadl_epi64((const __m128i*)&b[BPS * 3]);
  // Combine pair of lines.
  const __m128i a01 = _mm_unpacklo_epi32(a0, a1);
  const __m128i a23 = _mm_unpacklo_epi32(a2, a3);
  const __m128i b01 = _mm_unpacklo_epi32(b0, b1);
  const __m128i b23 = _mm_unpacklo_epi32(b2, b3);
  // Convert to 16b.
  const __m128i a01s = _mm_unpacklo_epi8(a01, zero);
  const __m128i a23s = _mm_unpacklo_epi8(a23, zero);
  const __m128i b01s = _mm_unpacklo_epi8(b01, zero);
  const __m128i b23s = _mm_unpacklo_epi8(b23, zero);
  // subtract, square and accumulate
  const __m128i d0 = _mm_subs_epi16(a01s, b01s);
  const __m128i d1 = _mm_subs_epi16(a23s, b23s);
  const __m128i e0 = _mm_madd_epi16(d0, d0);
  const __m128i e1 = _mm_madd_epi16(d1, d1);
  const __m128i sum = _mm_add_epi32(e0, e1);

  int32_t tmp[4];
  _mm_storeu_si128((__m128i*)tmp, sum);
  return (tmp[3] + tmp[2] + tmp[1] + tmp[0]);
}