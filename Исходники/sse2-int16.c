static long
conv_rgba16_rgbaF (const uint16_t *src, float *dst, long samples)
{
  long i = 0;

  if (((uintptr_t)src % 16) + ((uintptr_t)dst % 16) == 0)
    {
      long           n  = (samples / 2) * 2;
      const __m128i *s  = (const __m128i*) src;
            __v4sf  *d  = (__v4sf*) dst;

      for (; i < n / 2; i++)
        {
          /* Expand shorts to ints by loading zero in the high bits */
          const __m128i t0 = _mm_unpacklo_epi16 (s[i + 0], (__m128i)_mm_setzero_ps());
          const __m128i t1 = _mm_unpackhi_epi16 (s[i + 0], (__m128i)_mm_setzero_ps());

          /* Convert to float */
          const __m128  u0 = _mm_cvtepi32_ps (t0);
          const __m128  u1 = _mm_cvtepi32_ps (t1);

          const __v4sf rgba0 = u0 * u16_float;
          const __v4sf rgba1 = u1 * u16_float;

          d[2 * i + 0] = rgba0;
          d[2 * i + 1] = rgba1;
        }
      _mm_empty();
    }

  for (i *= 2 * 4; i != 4 * samples; i++)
    dst[i] = src[i] * (1.f / 65535);

  return samples;
}