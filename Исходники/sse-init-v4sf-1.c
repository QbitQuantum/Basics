test (float *v)
{
  __m128 x;

  x = _mm_set_ps (0, 0, 0, v[0]);
  check (x, v, 0);
  x = _mm_set_ps (0, 0, v[1], 0);
  check (x, v, 1);
  x = _mm_set_ps (0, v[2], 0, 0);
  check (x, v, 2);
  x = _mm_set_ps (v[3], 0, 0, 0);
  check (x, v, 3);
}