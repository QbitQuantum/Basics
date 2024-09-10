/**
 * This function represents the recursion formula.
 * @param r output 128-bit
 * @param a a 128-bit part of the internal state array
 * @param b a 128-bit part of the internal state array
 * @param d a 128-bit part of the internal state array (I/O)
 */
static inlinec void do_recursion(w128_t *r, w128_t *a, w128_t *b, w128_t *u) {
  __m128i x = a->si;
  __m128i z = _mm_slli_epi64(x, DSFMT_SL1);
  __m128i y = _mm_shuffle_epi32(u->si, SSE2_SHUFF);
  z = _mm_xor_si128(z, b->si);
  y = _mm_xor_si128(y, z);

  __m128i v = _mm_srli_epi64(y, DSFMT_SR);
  __m128i w = _mm_and_si128(y, sse2_param_mask.i128);
  v = _mm_xor_si128(v, x);
  v = _mm_xor_si128(v, w);
  r->si = v;
  u->si = y;
}