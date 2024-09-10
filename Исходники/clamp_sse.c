static void
clamphigh_u8_sse (uint8_t *dest, const uint8_t *src1, int n,
    const uint8_t *src2_1)
{
  __m128i xmm1;
  uint8_t max = *src2_1;

  /* Initial operations to align the destination pointer */
  for (; ((long)dest & 15) && (n > 0); n--) {
    uint8_t x = *src1++;
    if (x > max)
      x = max;
    *dest++ = x;
  }
  xmm1 = _mm_set1_epi8(max);
  for (; n >= 16; n -= 16) {
    __m128i xmm0;
    xmm0 = _mm_loadu_si128((__m128i *)src1);
    xmm0 = _mm_min_epu8(xmm0, xmm1);
    _mm_store_si128((__m128i *)dest, xmm0);
    dest += 16;
    src1 += 16;
  }
  for (; n > 0; n--) {
    uint8_t x = *src1++;
    if (x > max)
      x = max;
    *dest++ = x;
  }
}