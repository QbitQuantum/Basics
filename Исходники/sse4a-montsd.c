static void 
sse4a_test_movntsd (double *out, double *in)
{
  __m128d in_v2df = _mm_load_sd (in);
  _mm_stream_sd (out, in_v2df);
}