static void
sse4_1_test (void)
{
  union
    {
      __m128i x[NUM];
      unsigned char c[NUM * 16];
    } dst, src1, src2, mask;
  int i;

  init_pblendvb (src1.c, src2.c, mask.c);

  for (i = 0; i < NUM; i++)
    {
      dst.x[i] = _mm_blendv_epi8 (src1.x[i], src2.x[i], mask.x[i]);
      if (check_pblendvb (&dst.x[i], &src1.c[i * 16], &src2.c[i * 16],
			  &mask.c[i * 16]))
	abort ();
    }
}