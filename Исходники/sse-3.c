static inline
void
foo (__m128 *x)
{
  __m128 y = _mm_setzero_ps ();
  __m128 v = _mm_movehl_ps (y, *x);
  __m128 w = _mm_movehl_ps (*x, y);
  check (*x, 9, 1, 2, -3);
  check (v, 2, -3, 0, 0);
  check (w, 0, 0, 2, -3);
}