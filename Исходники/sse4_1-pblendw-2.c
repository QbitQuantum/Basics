static void
sse4_1_test (void)
{
  __m128i x, y;
  union
    {
      __m128i x[NUM];
      short s[NUM * 8];
    } dst, src1, src2;
  union
    {
      __m128i x;
      short s[8];
    } src3;
  int i;

  init_pblendw (src1.s, src2.s);

  /* Check pblendw imm8, m128, xmm */
  for (i = 0; i < NUM; i++)
    {
      dst.x[i] = _mm_blend_epi16 (src1.x[i], src2.x[i], MASK); 
      if (check_pblendw (&dst.x[i], &src1.s[i * 8], &src2.s[i * 8]))
	abort ();
    }
    
   /* Check pblendw imm8, xmm, xmm */
  src3.x = _mm_setzero_si128 ();

  x = _mm_blend_epi16 (dst.x[2], src3.x, MASK);
  y = _mm_blend_epi16 (src3.x, dst.x[2], MASK);

  if (check_pblendw (&x, &dst.s[16], &src3.s[0]))
    abort ();

  if (check_pblendw (&y, &src3.s[0], &dst.s[16]))
    abort ();
}