static void highbdRndingPacks(__m128i *u) {
  __m128i rnd = _mm_set1_epi32(1 << (FILTER_BITS - 1));
  u[0] = _mm_add_epi32(u[0], rnd);
  u[0] = _mm_srai_epi32(u[0], FILTER_BITS);
  u[0] = _mm_packus_epi32(u[0], u[0]);
}