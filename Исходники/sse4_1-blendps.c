static void
TEST (void)
{
  __m128 x, y;
  union
    {
      __m128 x[NUM];
      float f[NUM * 4];
    } dst, src1, src2;
  union
    {
      __m128 x;
      float f[4];
    } src3;
  int i;

  init_blendps (src1.f, src2.f);

  for (i = 0; i < 4; i++)
    src3.f[i] = (int) random ();

  /* Check blendps imm8, m128, xmm */
  for (i = 0; i < NUM; i++)
    {
      dst.x[i] = _mm_blend_ps (src1.x[i], src2.x[i], MASK); 
      if (check_blendps (&dst.x[i], &src1.f[i * 4], &src2.f[i * 4]))
	abort ();
    }
    
   /* Check blendps imm8, xmm, xmm */
  x = _mm_blend_ps (dst.x[2], src3.x, MASK);
  y = _mm_blend_ps (src3.x, dst.x[2], MASK);

  if (check_blendps (&x, &dst.f[8], &src3.f[0]))
    abort ();

  if (check_blendps (&y, &src3.f[0], &dst.f[8]))
    abort ();
}