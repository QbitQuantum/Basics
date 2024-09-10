__m128i
t3(__m128i a)
{
  return _mm_move_epi64(a);	/* 64-bit move between %xmm registers.  */
}