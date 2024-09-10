static WEBP_INLINE __m128i LoadUVPart(int u, int v) {
  const __m128i u_part = _mm_loadu_si128(&VP8kUtoRGBA[u].m);
  const __m128i v_part = _mm_loadu_si128(&VP8kVtoRGBA[v].m);
  const __m128i uv_part = _mm_add_epi32(u_part, v_part);
  return uv_part;
}