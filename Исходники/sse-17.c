sse2_test(void) {
  u a, b;
  a.v = setupa ();
  b.v = setupb ();
  if (untrue)
    bar(a.v, b.v);
  b.v = (__v4sf) _mm_movehl_ps ((__m128)a.v, (__m128)b.v);
  foo (a, b);
}