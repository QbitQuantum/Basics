static void
TEST (void)
{
  union128  s1, s2;
  int d[1];
  int e[1];

  s1.x = _mm_set_ps (24.43, 68.346, 43.35, 546.46);
  s2.x = _mm_set_ps (1.17, 2.16, 3.15, 4.14);
  d[0] = test (s1.x, s2.x); 
  e[0] = s1.a[0] > s2.a[0];

  if (checkVi (d, e, 1))
    abort ();
}