static void
sse4_1_test (void)
{
  union
    {
      __m128i x[NUM];
      int i[NUM * 4];
    } dst, src;
  int i;

  init_movntdqa (src.i);

  for (i = 0; i < NUM; i++)
    dst.x[i] = _mm_stream_load_si128 (&src.x[i]);

  for (i = 0; i < NUM; i++)
    if (memcmp (&dst.x[i], &src.x[i], sizeof(src.x[i])))
      abort ();
}