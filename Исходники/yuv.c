static WEBP_INLINE __m128i VP8GetRGBA32b(int y, int u, int v) {
  const __m128i u_part = _mm_loadu_si128(&VP8kUtoRGBA[u].m);
  const __m128i v_part = _mm_loadu_si128(&VP8kVtoRGBA[v].m);
  const __m128i y_part = _mm_loadu_si128(&VP8kYtoRGBA[y].m);
  const __m128i uv_part = _mm_add_epi32(u_part, v_part);
  const __m128i rgba1 = _mm_add_epi32(y_part, uv_part);
  const __m128i rgba2 = _mm_srai_epi32(rgba1, YUV_FIX2);
  return rgba2;
}