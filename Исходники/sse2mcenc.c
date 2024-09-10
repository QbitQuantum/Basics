/*Transpose 8 vectors with 8 16-bit values.*/
OD_SIMD_INLINE void od_transpose16x8(__m128i *t0, __m128i *t1,
 __m128i *t2, __m128i *t3,  __m128i *t4, __m128i *t5,
 __m128i *t6, __m128i *t7) {
  __m128i a0;
  __m128i b0;
  __m128i c0;
  __m128i d0;
  __m128i e0;
  __m128i f0;
  __m128i g0;
  __m128i h0;
  __m128i a1;
  __m128i b1;
  __m128i c1;
  __m128i d1;
  __m128i e1;
  __m128i f1;
  __m128i g1;
  __m128i h1;
  /*00112233*/
  a0 = _mm_unpacklo_epi16(*t0, *t1);
  b0 = _mm_unpacklo_epi16(*t2, *t3);
  c0 = _mm_unpacklo_epi16(*t4, *t5);
  d0 = _mm_unpacklo_epi16(*t6, *t7);
  /*44556677*/
  e0 = _mm_unpackhi_epi16(*t0, *t1);
  f0 = _mm_unpackhi_epi16(*t2, *t3);
  g0 = _mm_unpackhi_epi16(*t4, *t5);
  h0 = _mm_unpackhi_epi16(*t6, *t7);
  /*00001111*/
  a1 = _mm_unpacklo_epi32(a0, b0);
  b1 = _mm_unpacklo_epi32(c0, d0);
  /*22223333*/
  c1 = _mm_unpackhi_epi32(a0, b0);
  d1 = _mm_unpackhi_epi32(c0, d0);
  /*44445555*/
  e1 = _mm_unpacklo_epi32(e0, f0);
  f1 = _mm_unpacklo_epi32(g0, h0);
  /*66667777*/
  g1 = _mm_unpackhi_epi32(e0, f0);
  h1 = _mm_unpackhi_epi32(g0, h0);
  *t0 = _mm_unpacklo_epi64(a1, b1);
  *t1 = _mm_unpackhi_epi64(a1, b1);
  *t2 = _mm_unpacklo_epi64(c1, d1);
  *t3 = _mm_unpackhi_epi64(c1, d1);
  *t4 = _mm_unpacklo_epi64(e1, f1);
  *t5 = _mm_unpackhi_epi64(e1, f1);
  *t6 = _mm_unpacklo_epi64(g1, h1);
  *t7 = _mm_unpackhi_epi64(g1, h1);
}