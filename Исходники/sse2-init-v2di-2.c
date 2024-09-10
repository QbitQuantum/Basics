__m128i
test (long long b)
{
  return _mm_cvtsi64_si128 (b); 
}