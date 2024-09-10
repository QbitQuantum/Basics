void
check_mm_vmfrcz_sd (__m128d __A, __m128d __B)
{
  union128d a, b, c;
  double d[2];

  a.x = __A;
  b.x = __B;
  c.x = _mm_frcz_sd (__A, __B);
  d[0] = b.a[0] - (int)b.a[0] ;
  d[1] = a.a[1];
  if (check_union128d (c, d))
    abort ();
}