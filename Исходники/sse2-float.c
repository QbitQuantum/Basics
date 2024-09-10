static long
conv_rgbaF_linear_rgbAF_linear (const float *src, float *dst, long samples)
{
  long i = 0;
  long remainder;

  if (((uintptr_t)src % 16) + ((uintptr_t)dst % 16) == 0)
    {
      const long    n = (samples / 2) * 2;
      const __v4sf *s = (const __v4sf*) src;
            __v4sf *d = (__v4sf*)dst;

      for ( ; i < n; i += 2)
        {
          __v4sf rbaa0, rbaa1;
        
          __v4sf rgba0 = *s++;
          __v4sf rgba1 = *s++;

          /* Expand alpha */
          __v4sf aaaa0 = (__v4sf)_mm_shuffle_epi32((__m128i)rgba0, _MM_SHUFFLE(3, 3, 3, 3));
          __v4sf aaaa1 = (__v4sf)_mm_shuffle_epi32((__m128i)rgba1, _MM_SHUFFLE(3, 3, 3, 3));
          
          /* Premultiply */
          rgba0 = rgba0 * aaaa0;
          rgba1 = rgba1 * aaaa1;
          
          /* Shuffle the original alpha value back in */
          rbaa0 = _mm_shuffle_ps(rgba0, aaaa0, _MM_SHUFFLE(0, 0, 2, 0));
          rbaa1 = _mm_shuffle_ps(rgba1, aaaa1, _MM_SHUFFLE(0, 0, 2, 0));
          
          rgba0 = _mm_shuffle_ps(rgba0, rbaa0, _MM_SHUFFLE(2, 1, 1, 0));
          rgba1 = _mm_shuffle_ps(rgba1, rbaa1, _MM_SHUFFLE(2, 1, 1, 0));
          
          *d++ = rgba0;
          *d++ = rgba1;
        }
      _mm_empty ();
    }

  dst += i * 4;
  src += i * 4;
  remainder = samples - i;
  while (remainder--)
  {
    const float a = src[3];
    dst[0] = src[0] * a;
    dst[1] = src[1] * a;
    dst[2] = src[2] * a;
    dst[3] = a;
    
    src += 4;
    dst += 4;
  }

  return samples;
}