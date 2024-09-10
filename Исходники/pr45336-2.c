unsigned long long int foo32(__m128i x)
{ 
  return (unsigned int) _mm_extract_epi32(x, 2);
}