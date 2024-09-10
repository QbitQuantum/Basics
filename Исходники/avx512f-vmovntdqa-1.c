void extern
avx512f_test (void)
{
  y = _mm512_stream_load_si512 (x);
}