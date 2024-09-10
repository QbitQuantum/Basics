static long long 
sse4a_test_extrqi (long long in)
{
  __m128i v1;
  long long pad =0x0;
  LI v_out;
  v1 = _mm_set_epi64x (pad, in);
  v_out.vec = _mm_extracti_si64 (v1, (unsigned int) 0x10,(unsigned int) 0x08);
  return (v_out.i[0]);
}