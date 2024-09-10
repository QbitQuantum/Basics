__m128i
foo (short *x, struct S *y, __m128i *z)
{
  struct S s = *y;
  ((T *) &s.d)[0] = *x;
  return _mm_cmpeq_epi16 (s.d, *z);
}