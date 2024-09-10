static long long
sse4a_test_inserti (long long in1, long long in2)
{
  __m128i v1,v2;
  long long pad = 0x0;
  LI v_out;
  v1 = _mm_set_epi64x (pad, in1);
  v2 = _mm_set_epi64x (pad, in2); 
  v_out.vec = _mm_inserti_si64 (v1, v2, (unsigned int) 0x10, (unsigned int) 0x08);
  return (v_out.i[0]);  
}