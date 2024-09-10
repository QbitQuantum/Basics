void
check_mm_fnmsub_sd (__m128d __A, __m128d __B, __m128d __C)
{
  union128d a, b, c, e;
  a.x = __A;
  b.x = __B;
  c.x = __C;
  double d[2];
  int i;
  e.x = _mm_fnmsub_sd (__A, __B, __C);
  for (i = 1; i < 2; i++)
    {
      d[i] = a.a[i];
    }
  d[0] = -a.a[0] * b.a[0] - c.a[0];
  if (check_union128d (e, d))
    abort ();
}