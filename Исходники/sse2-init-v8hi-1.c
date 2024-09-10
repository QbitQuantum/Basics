test (unsigned short *v)
{
  __m128i x;

  x = _mm_set_epi16 (0, 0, 0, 0, 0, 0, 0, v[0]);
  check (x, v, 0);
  x = _mm_set_epi16 (0, 0, 0, 0, 0, 0, v[1], 0);
  check (x, v, 1);
  x = _mm_set_epi16 (0, 0, 0, 0, 0, v[2], 0, 0);
  check (x, v, 2);
  x = _mm_set_epi16 (0, 0, 0, 0, v[3], 0, 0, 0);
  check (x, v, 3);
  x = _mm_set_epi16 (0, 0, 0, v[4], 0, 0, 0, 0);
  check (x, v, 4);
  x = _mm_set_epi16 (0, 0, v[5], 0, 0, 0, 0, 0);
  check (x, v, 5);
  x = _mm_set_epi16 (0, v[6], 0, 0, 0, 0, 0, 0);
  check (x, v, 6);
  x = _mm_set_epi16 (v[7], 0, 0, 0, 0, 0, 0, 0);
  check (x, v, 7);
}