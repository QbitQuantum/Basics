static inline char* stream_fill(char* dst, size_t* n, const __m128i data)
{
  while (*n >= SSE_SIZE)
  {
    _mm_stream_si128((__m128i*) dst, data);
    
    dst += SSE_SIZE;
    *n  -= SSE_SIZE;
  }
  return dst;
}