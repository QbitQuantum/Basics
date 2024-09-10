static __m128i S(__m128i x, int i) {
  const __m128i a0 = _mm_shuffle_epi8(x, g_shuffles[i][0]);
  const __m128i b0 = _mm_shuffle_epi8(x, g_shuffles[i][1]);

  const __m128i a1 = _mm_min_epi8(a0, b0);
  const __m128i b1 = _mm_max_epi8(a0, b0);

  const __m128i a2 = _mm_shuffle_epi8(a1, g_shuffles[i][2]);
  const __m128i b2 = _mm_shuffle_epi8(b1, g_shuffles[i][3]);

  return _mm_or_si128(a2, b2);
}