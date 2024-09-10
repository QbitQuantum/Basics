void
check_mm256_fmsub_pd (__m256d __A, __m256d __B, __m256d __C)
{
  union256d a, b, c, e;
  a.x = __A;
  b.x = __B;
  c.x = __C;
  double d[4];
  int i;
  e.x = _mm256_fmsub_pd (__A, __B, __C);
  for (i = 0; i < 4; i++)
    {
      d[i] = a.a[i] * b.a[i] - c.a[i];
    }
  if (check_union256d (e, d))
    abort ();
}