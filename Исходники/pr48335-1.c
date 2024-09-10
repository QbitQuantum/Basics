void
f2 (__m128d x)
{
  struct S s;
  _mm_store_pd ((double *) &s.d, x);
  __real__ s.d *= 7.0;
  bar (s);
}