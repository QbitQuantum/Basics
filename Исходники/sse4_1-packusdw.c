static void
TEST (void)
{
  union
    {
      __m128i x[NUM / 4];
      int i[NUM];
    } src1, src2;
  union
    {
      __m128i x[NUM / 4];
      unsigned short s[NUM * 2];
    } dst;
  int i, sign = 1;

  for (i = 0; i < NUM; i++)
    {
      src1.i[i] = i * i * sign;
      src2.i[i] = (i + 20) * sign;
      sign = -sign;
    }

  for (i = 0; i < NUM; i += 4)
    dst.x[i / 4] = _mm_packus_epi32 (src1.x [i / 4], src2.x [i / 4]);

  for (i = 0; i < NUM; i ++)
    {
      int dstIndex;
      unsigned short sVal;

      sVal = int_to_ushort (src1.i[i]);
      dstIndex = (i % 4) + (i / 4) * 8;
      if (sVal != dst.s[dstIndex])
	abort ();

      sVal = int_to_ushort (src2.i[i]);
      dstIndex += 4;
      if (sVal != dst.s[dstIndex])
	abort ();
    }
}