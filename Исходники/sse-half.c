static inline long
conv_yF_yHalf (const float *src, uint16_t *dst, long samples)
{
  const __v4sf *s_vec;
  uint64_t     *d_vec;

  long n = samples;

  s_vec = (const __v4sf *)src;
  d_vec = (uint64_t *)dst;

  while (n >= 4)
    {
      __m128 in_val = _mm_loadu_ps((float *)s_vec++);
      __m128i out_val = _mm_cvtps_ph(in_val, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
      _mm_storel_epi64((__m128i *)d_vec++, out_val);
      n -= 4;
    }

  src = (const float *)s_vec;
  dst = (uint16_t *)d_vec;

  while (n)
    {
      __m128 in_val = _mm_load_ss(src++);
      __m128i out_val = _mm_cvtps_ph(in_val, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
      *dst++ = _mm_extract_epi16(out_val, 0);
      n -= 1;
    }

  return samples;
}