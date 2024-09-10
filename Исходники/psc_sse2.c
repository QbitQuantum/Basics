inline __m128i 
func_mul_epu32(__m128i a, __m128i b){
#if 1
  // Multiply elements 0 and 2, and bput the 64 bit results into a vector.
  __m128i tmp02 = _mm_mul_epu32(a, b);
  // Shift the vectors by one word to the right, making 3->2, and 1->0, and 
  // then multiply into double word vector.
  __m128i tmp13 = _mm_mul_epu32( _mm_srli_si128(a, 4), _mm_srli_si128(b,4));
  // Shuffle the vectors to place the lower 32 bits of each results in the
  // lower two words. I have some concerns about endianness and portability
  // related to this function. 
  __m128i tmpres02 = _mm_shuffle_epi32(tmp02, _MM_SHUFFLE(0,0,2,0));
  __m128i tmpres13 = _mm_shuffle_epi32(tmp13, _MM_SHUFFLE(0,0,2,0));
  // upcack the shuffled vectors into a return value
  return _mm_unpacklo_epi32(tmpres02, tmpres13);
#else
  pvInt ret;
  int * p_a;
  int * p_b;
  p_a = (int *)&a;
  p_b = (int *)&b;
  for(int m=0; m < VEC_SIZE; m++){
    ret.v[m] = p_a[m] * p_b[m];
  }
  return ret.r;
#endif
    
}