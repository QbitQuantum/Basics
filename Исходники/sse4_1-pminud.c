static void
sse4_1_test (void)
{
  union
    {
      __m128i x[NUM / 4];
      unsigned int i[NUM];
    } dst, src1, src2;
  int i;
  unsigned int min;

  for (i = 0; i < NUM; i++)
    {
      src1.i[i] = i * i;
      src2.i[i] = i + 20;
      if ((i % 4))
	src2.i[i] |= 0x80000000;
    }

  for (i = 0; i < NUM; i += 4)
    dst.x[i / 4] = _mm_min_epu32 (src1.x[i / 4], src2.x[i / 4]);

  for (i = 0; i < NUM; i++)
    {
      min = src1.i[i] >= src2.i[i] ? src2.i[i] : src1.i[i];
      if (min != dst.i[i])
	abort ();
    }
}