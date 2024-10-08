static void
TEST (void)
{
  union
    {
      __m128i x[NUM / 2];
      long long ll[NUM];
    } dst;
  union
    {
      __m128i x[NUM / 2];
      int i[NUM * 2];
    } src1, src2;
  int i, sign = 1;
  long long value;

  for (i = 0; i < NUM * 2; i += 2)
    {
      src1.i[i] = i * i * sign;
      src2.i[i] = (i + 20) * sign;
      sign = -sign;
    }

  for (i = 0; i < NUM; i += 2)
    dst.x[i / 2] = _mm_mul_epi32 (src1.x[i / 2], src2.x[i / 2]);

  for (i = 0; i < NUM; i++)
    {
      value = (long long) src1.i[i * 2] * (long long) src2.i[i * 2];
      if (value != dst.ll[i])
	abort ();
    }
}