static void
sse4_1_test (void)
{
  union
    {
      __m128d x[NUM];
      double d[NUM * 2];
    } dst, src1, src2, mask;
  int i;

  init_blendvpd (src1.d, src2.d, mask.d);

  for (i = 0; i < NUM; i++)
    {
      dst.x[i] = _mm_blendv_pd (src1.x[i], src2.x[i], mask.x[i]);
      if (check_blendvpd (&dst.x[i], &src1.d[i * 2], &src2.d[i * 2],
			  &mask.d[i * 2]))
	abort ();
    }
}