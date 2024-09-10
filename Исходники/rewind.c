static INLINE size_t find_change(const uint16_t *a, const uint16_t *b)
{
   const __m128i *a128 = (const __m128i*)a;
   const __m128i *b128 = (const __m128i*)b;
	
   for (;;)
   {
      __m128i v0    = _mm_loadu_si128(a128);
      __m128i v1    = _mm_loadu_si128(b128);
      __m128i c     = _mm_cmpeq_epi32(v0, v1);
      uint32_t mask = _mm_movemask_epi8(c);

      if (mask != 0xffff) /* Something has changed, figure out where. */
      {
         size_t ret = (((uint8_t*)a128 - (uint8_t*)a) |
               (compat_ctz(~mask))) >> 1;
			return ret | (a[ret] == b[ret]);
      }

      a128++;
      b128++;
   }